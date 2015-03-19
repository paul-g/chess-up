#include "resource.hpp"

std::string png(std::string name) {
	return "../img/" + name + ".png";
}

std::string resource::wbishop() {
	return png("white_bishop");
}

std::string resource::bbishop() {
	return png("black_bishop");
}

std::string resource::wking() {
	return png("white_king");
}

std::string resource::bking() {
	return png("black_king");
}

std::string resource::wknight() {
	return png("white_knight");
}

std::string resource::bknight() {
	return png("black_knight");
}

std::string resource::wpawn() {
	return png("white_pawn");
}

std::string resource::bpawn() {
	return png("black_pawn");
}

std::string resource::wqueen() {
	return png("white_queen");
}

std::string resource::bqueen() {
	return png("black_queen");
}

std::string resource::wrook() {
	return png("white_rook");
}

std::string resource::brook() {
	return png("black_rook");
}

std::string resource::freeSerif() {
	return "../fonts/FreeSerif.ttf";
}
