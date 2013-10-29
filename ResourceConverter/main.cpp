#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
    system("title Resource Converter");
    al_init();
    al_init_image_addon();
    string path, path2, type;

    while(1) {
        system("cls");
        cout << "Type EXIT to exit.\n\nType: 'Convert file' 'New name'+RES 'Type'";
        cout << "\nType: RES_BITMAP / RES_AUDIO";
        cout << "\n\nExample:   file.png file RES_BITMAP\n\n\n>> ";
        cin >> path >> path2 >> type;
        path2 += ".RES";

        if     (type == "RES_BITMAP") type = "1";
        else if(type == "RES_AUDIO")  type = "2";
        else                          type = "0";

        if(path == "EXIT" || path == "exit")
            break;

        if(type == "1") { // RES_BITMAP
            ALLEGRO_BITMAP* img = al_load_bitmap(path.c_str());
            ALLEGRO_COLOR color;

            if(!img) cout << "\nCannot open this file!";
            else {
                fstream file(path2.c_str(), ios::out);

                file << al_get_bitmap_width(img) << " " << al_get_bitmap_height(img) << " 1 ";

                al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
                for(int x = 0; x < al_get_bitmap_width(img); ++x) {
                    for(int y = 0; y < al_get_bitmap_height(img); ++y) {
                        color = al_get_pixel(img, x, y);
                        file << int(color.r*255) << " " << int(color.g*255) << " " << int(color.b*255) << " " << int(color.a*255) << " ";
                    }
                }
                al_unlock_bitmap(img);
            }
        } else {
            cout << "\nWrong type!";
        }

        cout << "\nType anything to continue.";

        getch();
    }

    return 0;
}
