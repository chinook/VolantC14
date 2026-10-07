#include <gui/ui_splash_screen/UI_splashView.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Application.hpp>

UI_splashView::UI_splashView()
{

}

void UI_splashView::handleTickEvent()
{
    UI_splashViewBase::handleTickEvent();

    tickCounter++;

    /* Progression 0..100 % sur la duree du splash (SPLASH_TICKS ticks).
     * La barre loading_box (plage 0..100) se remplit au rythme du compteur. */
    int progress = (int)((tickCounter * 100U) / SPLASH_TICKS);
    if (progress > 100) progress = 100;
    loading_box.setValue(progress);

    if (tickCounter >= SPLASH_TICKS)
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
