#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <tuple>
#include "RenderWindow.hpp"
#include "Text.hpp"

RenderWindow::RenderWindow(const char* p_title, const int p_w, const int p_h)
	:window_(NULL), renderer_(NULL) {
	window_ = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_HIDDEN);

	if (window_ == nullptr) {
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer_ == nullptr) {
		std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
	}
}

SDL_Texture* RenderWindow::loadTexture(const char* file_path) {
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(renderer_, file_path);

	if (texture == nullptr)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::cleanUp() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer_);
}

void RenderWindow::clear(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer_, r, g, b, a);        
	SDL_RenderClear(renderer_);
}

void RenderWindow::clear(SDL_Color color, int a) {
	SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, a);        
	SDL_RenderClear(renderer_);
}

void RenderWindow::setIcon(const char* file_path) {
	icon_ = IMG_Load(file_path);
	SDL_SetWindowIcon(window_, icon_);
}

void RenderWindow::changeColor(SDL_Color color) {
	SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);        
}

void RenderWindow::render(Text text, bool centered) const {
	SDL_Rect text_rect;
	if (centered) {
		text_rect = text.renderCenteredTextInfo();
	} else {
		text_rect = text.renderTextInfo();
	}
	SDL_RenderCopy(renderer_, text.getFgTex(), nullptr, &text_rect);
}

void RenderWindow::render(std::tuple<SDL_Rect, SDL_Rect> rects, SDL_Texture* tex) const {
	SDL_RenderCopy(renderer_, tex, &std::get<0>(rects), &std::get<1>(rects));
}

void RenderWindow::render(const BasicButton &button) {
	if (button.visible_ == false) {
		return;
	}
	changeColor(button.background_color_);
	SDL_RenderFillRect(renderer_, &button.rect_);
	changeColor(button.border_color_);
	if (button.border_thickness_ == 1) {
		SDL_RenderDrawRect(renderer_, &button.rect_);
	} else {
		SDL_Rect top_rect = {button.rect_.x, button.rect_.y, button.rect_.w, button.border_thickness_};
		SDL_Rect bot_rect = {button.rect_.x, button.rect_.y + button.rect_.h - button.border_thickness_, button.rect_.w, button.border_thickness_};
		SDL_Rect left_rect = {button.rect_.x, button.rect_.y, button.border_thickness_, button.rect_.h};
		SDL_Rect right_rect = {button.rect_.x + button.rect_.w - button.border_thickness_, button.rect_.y, button.border_thickness_, button.rect_.h};
		SDL_RenderFillRect(renderer_, &top_rect);
		SDL_RenderFillRect(renderer_, &bot_rect);
		SDL_RenderFillRect(renderer_, &left_rect);
		SDL_RenderFillRect(renderer_, &right_rect);
	}
	render(button.text_);
}

void RenderWindow::renderLine(int x1, int y1, int x2, int y2, SDL_Color color) {
	changeColor(color);
	SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
}

void RenderWindow::renderRect(SDL_Rect rect, SDL_Color color) {
	changeColor(color);
	SDL_RenderFillRect(renderer_, &rect);
}

void RenderWindow::renderBlendedRect(SDL_Rect rect, SDL_Color color) {
	changeColor(color);
	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer_, &rect);
	SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_NONE);
}

void RenderWindow::display() const {
	SDL_RenderPresent(renderer_);
}

void RenderWindow::showWindow() {
	SDL_ShowWindow(window_);
}