#include <iostream>
#include <chrono>
#include <string>
#include "SDL.h"
#include "Skia.h"

int main(int argc, char * argv[]) {
    SDL sdl("Hello, world!", 255, 255);
    Skia skia(255, 255);
    bool is_running = true;
    int FPS = 60;
    double rotation = 0;
    double rotation_speed = 0.5;
    double i_double = 0;
    int i = 0;
    int i2 = 0;
    std::string str;

    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
                break;
            }
        }
        sdl.draw([&](SDL_Renderer* _ren){
            skia.draw(_ren, [&](SkCanvas* cv){
                rotation += rotation_speed;
                i_double += 0.3;
                i = i_double;
                i2++;
                cv->save();
                cv->rotate(rotation, 127, 127);
                cv->drawColor(SkColorSetRGB(5,5,20));
                

                SkPaint paint;
                paint.setStyle(SkPaint::kStroke_Style);
                paint.setStrokeWidth(1);
                paint.setAntiAlias(true);

                SkRect rect = SkRect::MakeXYWH(50-(i%100/2), 50-(i%100/2), 40+i%100, 60+i%100);
                paint.setColor(SK_ColorWHITE);
                cv->drawRect(rect, paint);

                SkRRect oval;
                oval.setOval(rect);
                oval.offset(40, 60);
                paint.setColor(SK_ColorWHITE);
                cv->drawRRect(oval, paint);

                paint.setColor(SK_ColorWHITE);
                cv->drawCircle(180, 50, 0+i%30, paint);
                cv->drawCircle(180, 120, 0+i%30, paint);
                cv->drawCircle(180, 190, 0+i%30, paint);

                rect.offset(80, 0);
                paint.setColor(SK_ColorWHITE);
                cv->drawRoundRect(rect, 10, 10, paint);

                SkPath path;
                path.cubicTo(768, 0, -512, 256, 256, 256);
                paint.setColor(SK_ColorWHITE);
                cv->drawPath(path, paint);
                
                cv->saveLayer(nullptr, nullptr);
                cv->rotate(-rotation, 120, 120);

                    str = std::string(
                        "Hello, Skia! fp: ")
                        + std::to_string(i2)
                    ;
                    SkPaint paint2;
                    paint2.setStrokeWidth(1);
                    paint2.setAntiAlias(true);
                    paint2.setColor(SkColorSetRGB(200,200,255));
                    auto text = SkTextBlob::MakeFromString(str.c_str(), SkFont(nullptr, 14));
                    cv->drawTextBlob(text.get(), 120, 120, paint2);

                cv->restore();
                cv->restore();
            });
        });
        SDL_Delay(1000 / FPS);
    }
    return 0;
}