#ifndef UI_SPLASHVIEW_HPP
#define UI_SPLASHVIEW_HPP

#include <gui_generated/ui_splash_screen/UI_splashViewBase.hpp>
#include <gui/ui_splash_screen/UI_splashPresenter.hpp>

class UI_splashView : public UI_splashViewBase
{
public:
    UI_splashView();
    virtual ~UI_splashView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    virtual void handleTickEvent();
private:
    uint32_t tickCounter = 0;
    static const uint32_t SPLASH_TICKS = 180;
};

#endif // UI_SPLASHVIEW_HPP
