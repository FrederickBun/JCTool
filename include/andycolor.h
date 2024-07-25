#ifndef __ANDYCOLOR_H__
#define __ANDYCOLOR_H__
#include<Windows.h>
#include<iostream>
namespace color{
    static const WORD bgMask(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
    static const WORD fgMask(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    static const WORD fgBlack(0);
    static const WORD fgLoRed(FOREGROUND_RED);
    static const WORD fgLoGreen(FOREGROUND_GREEN);
    static const WORD fgLoBlue(FOREGROUND_BLUE);
    static const WORD fgLoCyan(fgLoGreen | fgLoBlue);
    static const WORD fgLoMagenta(fgLoRed | fgLoBlue);
    static const WORD fgLoYellow(fgLoRed | fgLoGreen);
    static const WORD fgLoWhite(fgLoRed | fgLoGreen | fgLoBlue);
    static const WORD fgGray(fgBlack | FOREGROUND_INTENSITY);
    static const WORD fgHiWhite(fgLoWhite | FOREGROUND_INTENSITY);
    static const WORD fgHiBlue(fgLoBlue | FOREGROUND_INTENSITY);
    static const WORD fgHiGreen(fgLoGreen | FOREGROUND_INTENSITY);
    static const WORD fgHiRed(fgLoRed | FOREGROUND_INTENSITY);
    static const WORD fgHiCyan(fgLoCyan | FOREGROUND_INTENSITY);
    static const WORD fgHiMagenta(fgLoMagenta | FOREGROUND_INTENSITY);
    static const WORD fgHiYellow(fgLoYellow | FOREGROUND_INTENSITY);
    static const WORD bgBlack(0);
    static const WORD bgLoRed(BACKGROUND_RED);
    static const WORD bgLoGreen(BACKGROUND_GREEN);
    static const WORD bgLoBlue(BACKGROUND_BLUE);
    static const WORD bgLoCyan(bgLoGreen | bgLoBlue);
    static const WORD bgLoMagenta(bgLoRed | bgLoBlue);
    static const WORD bgLoYellow(bgLoRed | bgLoGreen);
    static const WORD bgLoWhite(bgLoRed | bgLoGreen | bgLoBlue);
    static const WORD bgGray(bgBlack | BACKGROUND_INTENSITY);
    static const WORD bgHiWhite(bgLoWhite | BACKGROUND_INTENSITY);
    static const WORD bgHiBlue(bgLoBlue | BACKGROUND_INTENSITY);
    static const WORD bgHiGreen(bgLoGreen | BACKGROUND_INTENSITY);
    static const WORD bgHiRed(bgLoRed | BACKGROUND_INTENSITY);
    static const WORD bgHiCyan(bgLoCyan | BACKGROUND_INTENSITY);
    static const WORD bgHiMagenta(bgLoMagenta | BACKGROUND_INTENSITY);
    static const WORD bgHiYellow(bgLoYellow | BACKGROUND_INTENSITY);
    void setConsoleColor(WORD mask, WORD c){
        static HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        if(hStdout==NULL)return;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hStdout, &csbi);
        csbi.wAttributes &= ~mask;
        csbi.wAttributes |= c;
        SetConsoleTextAttribute(hStdout, csbi.wAttributes);
    }
    void setfgConsoleColor(WORD c){setConsoleColor(fgMask,c);}
    void setbgConsoleColor(WORD c){setConsoleColor(bgMask,c);}
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_white(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgLoWhite);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_blue(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgHiBlue);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_green(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgHiGreen);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_red(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgHiRed);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_cyan(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgHiCyan);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_magenta(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgHiMagenta);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_yellow(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgHiYellow);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& fg_black(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(fgMask, fgBlack);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_white(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgLoWhite);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_blue(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgHiBlue);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_green(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgHiGreen);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_red(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgHiRed);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_cyan(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgHiCyan);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_magenta(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgHiMagenta);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_yellow(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgHiYellow);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& bg_black(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgBlack);
        return os;
    }
    template<typename charT, typename traits>
    std::basic_ostream<charT, traits>& clr(std::basic_ostream<charT, traits>& os){
        os.flush();
        setConsoleColor(bgMask, bgBlack);
        setConsoleColor(fgMask, fgLoWhite);
        system("cls");
        return os;
    }
}
#endif
