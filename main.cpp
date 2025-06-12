
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
using namespace std;

bool init();
void kill();
bool load();
bool LoadImage(std::string imagePath, SDL_Surface* destination);

// Pointers to our window and surfaces
SDL_Window* window;
SDL_Surface* winSurface;


SDL_Surface* PieceSurfaces[12];

string Pieces[6] = {
	"pawn", "knight", "bishop", "rook", "queen", "king"
};


void DrawPieceAt(int piece, int x, int y, int size){
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	destination.w = size;
	destination.h = size;

	SDL_BlitScaled(PieceSurfaces[piece], NULL, winSurface, &destination);
	SDL_UpdateWindowSurface( window );
}


int main(int argc, char** args) {

	if ( !init() ) return 1;
	if ( !load() ) return 1;

	cout<<"test\n";

	for(int piece = 0; piece < 6; piece++){
		int pieceX = 130 + piece * 50;
		int pieceY = 130 + piece * 10;
		DrawPieceAt(piece, pieceX, pieceY, 50);
	}

	for(int piece = 6; piece < 12; piece++){
		int pieceX = 130 + piece * 30;
		int pieceY = 260 + piece * 5;
		DrawPieceAt(piece, pieceX, pieceY, 50);
	}
	

	// Update window
	SDL_UpdateWindowSurface( window );
	while(true) {
		SDL_Delay(100);
	}

	kill();
	return 0;
}


bool init() {
	// See last example for comments
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		system("pause");
		return false;
	} 

	window = SDL_CreateWindow( "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
	if ( !window ) {
		cout << "Error creating window: " << SDL_GetError()  << endl;
		system("pause");
		return false;
	}

	winSurface = SDL_GetWindowSurface( window );
	if ( !winSurface ) {
		cout << "Error getting surface: " << SDL_GetError() << endl;
		system("pause");
		return false;
	}
	return true;
}

bool load(){
	for(int piece = 0; piece < 12; piece++){
		SDL_Surface* temp;

		
		bool isPieceWhite = piece < 6;
		int pieceNameIndex = piece % 6;
		string pieceFilePath = (isPieceWhite ?  "WhitePieces/" : "BlackPieces/") + Pieces[pieceNameIndex] + ".bmp";
		std::cout<<pieceFilePath<<"\n\n";

		std::cout<< "Piece % 6 = "<< piece % 6 <<"\t"<<Pieces[pieceNameIndex]<<"\n";

		temp = SDL_LoadBMP(pieceFilePath.c_str());

		if(!temp){
			std::cout << "Error loading image: " << SDL_GetError() << endl;
			return false;
		}

		PieceSurfaces[piece] = SDL_ConvertSurface(temp, winSurface->format, 0);


		SDL_FreeSurface(temp);

		// Make sure format succeeded
		if ( !PieceSurfaces[piece] ) {
			cout << "Error converting surface: " << SDL_GetError() << endl;
			return false;
		}
	}
	return true;
}

void kill() {
	std::cout<<"killing\n\n";
	// Free images
	for(int piece=0; piece<12; piece++){
		SDL_FreeSurface(PieceSurfaces[piece]);
	}

	// Quit
	SDL_DestroyWindow( window );
	SDL_Quit();
}