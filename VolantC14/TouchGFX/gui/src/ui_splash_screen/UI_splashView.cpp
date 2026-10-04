#include <gui/ui_splash_screen/UI_splashView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Application.hpp>

UI_splashView::UI_splashView()
{

}

void UI_splashView::handleTickEvent()
{
    UI_splashViewBase::handleTickEvent();
    if (++tickCounter >= SPLASH_TICKS)
    {
        static_cast<FrontendApplication*>(touchgfx::Application::getInstance())
            ->gotoUI_page1ScreenNoTransition();
    }
}

void UI_splashView::setupScreen()
{
    UI_splashViewBase::setupScreen();
}

void UI_splashView::tearDownScreen()
{
    UI_splashViewBase::tearDownScreen();
}
