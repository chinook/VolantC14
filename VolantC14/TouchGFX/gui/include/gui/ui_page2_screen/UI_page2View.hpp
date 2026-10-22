#ifndef UI_PAGE2VIEW_HPP
#define UI_PAGE2VIEW_HPP

#include <gui_generated/ui_page2_screen/UI_page2ViewBase.hpp>
#include <gui/ui_page2_screen/UI_page2Presenter.hpp>

class UI_page2View : public UI_page2ViewBase
{
public:
    UI_page2View();
    virtual ~UI_page2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Simulateur : la barre d'espace revient a l'ecran 1 (voir .cpp, #ifdef SIMULATOR)
    virtual void handleKeyEvent(uint8_t key);

    virtual void change_screen(uint8_t screen);
    virtual void update_power(float power);
    virtual void update_efficiency(float eff);
    virtual void update_tsr(float tsr);
    virtual void update_speed(float speed);
    virtual void update_gear(float gear);
    virtual void update_gear_ratio(float gear_ratio);
    virtual void update_rotor_speed(float rotor_speed);
    virtual void update_mast_angle(float mast_angle);
    virtual void update_wind_dir(float wind_dir);
    virtual void update_wind_speed(float wind_speed);
    virtual void update_pitch_cmd(float pitch_cmd);
    virtual void update_pitch(float pitch);
    virtual void update_fps(float fps);
protected:
};

#endif // UI_PAGE2VIEW_HPP
