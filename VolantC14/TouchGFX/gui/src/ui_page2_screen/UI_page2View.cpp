#include <gui/ui_page2_screen/UI_page2View.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Application.hpp>

UI_page2View::UI_page2View()
{

}

void UI_page2View::setupScreen()
{
    UI_page2ViewBase::setupScreen();
}

void UI_page2View::tearDownScreen()
{
    UI_page2ViewBase::tearDownScreen();
}

void UI_page2View::change_screen(uint8_t screen)
{
	UI_page2ViewBase::handleKeyEvent(screen);
}

void UI_page2View::handleKeyEvent(uint8_t key)
{
#ifdef SIMULATOR
	/* Dans le simulateur PC, la barre d'espace (' ' = 32) revient a l'ecran 1.
	 * Guard SIMULATOR : aucun effet sur la carte. */
	if (key == ' ')
	{
		static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoUI_page1ScreenNoTransition();
		return;
	}
#endif
	UI_page2ViewBase::handleKeyEvent(key);
}

/* NOTE : la page 2 a ete redessinee dans le Designer. Les widgets de valeur
 * deviennent un par un des wildcards avec buffer (modele <0>, valeur par defaut
 * "--", Use Buffer, taille 10) ; chacun a sa fonction update_... ci-dessous,
 * appelee par UI_page2Presenter::update_ui.
 * Tous les widgets de valeur sont branches, sauf batt_value et torque_value
 * (textes fixes "--" : aucune donnee CAN pour la batterie ni le couple).
 * update_power() reste un no-op (widget retire). */
void UI_page2View::update_power(float power)
{
	(void)power;
}

void UI_page2View::update_efficiency(float eff)
{
	Unicode::snprintfFloat(efficiency_valueBuffer, EFFICIENCY_VALUE_SIZE, "%.0f", eff);
	efficiency_value.invalidate();
}

void UI_page2View::update_speed(float speed)
{
	Unicode::snprintfFloat(speed_valueBuffer, SPEED_VALUE_SIZE, "%.1f", speed);
	speed_value.invalidate();
}

void UI_page2View::update_gear(float gear)
{
	Unicode::snprintfFloat(gear_valueBuffer, GEAR_VALUE_SIZE, "%.0f", gear);
	gear_value.invalidate();
}

void UI_page2View::update_gear_ratio(float gear_ratio)
{
	Unicode::snprintfFloat(gear_ratio_valueBuffer, GEAR_RATIO_VALUE_SIZE, "%.1f", gear_ratio);
	gear_ratio_value.invalidate();
}

void UI_page2View::update_tsr(float tsr_temps)
{
	Unicode::snprintfFloat(tsr_valueBuffer, TSR_VALUE_SIZE, "%.1f", tsr_temps);
	tsr_value.invalidate();
}

void UI_page2View::update_rotor_speed(float rotor_speed)
{
	Unicode::snprintfFloat(rotor_valueBuffer, ROTOR_VALUE_SIZE, "%.0f", rotor_speed);
	rotor_value.invalidate();
}

void UI_page2View::update_mast_angle(float mast_angle)
{
	/* Mario envoie -999 tant que le mat n'est pas calibre (bouton BG) -> "--" */
	if (mast_angle <= -998.0f)
	{
		Unicode::strncpy(mast_valueBuffer, "--", MAST_VALUE_SIZE);
	}
	else
	{
		Unicode::snprintfFloat(mast_valueBuffer, MAST_VALUE_SIZE, "%.1f", mast_angle);
	}
	mast_value.invalidate();
}

void UI_page2View::update_wind_dir(float wind_dir)
{
	Unicode::snprintfFloat(wind_dir_valueBuffer, WIND_DIR_VALUE_SIZE, "%.0f", wind_dir);
	wind_dir_value.invalidate();
}

void UI_page2View::update_wind_speed(float wind_speed)
{
	Unicode::snprintfFloat(wind_valueBuffer, WIND_VALUE_SIZE, "%.1f", wind_speed);
	wind_value.invalidate();
}

void UI_page2View::update_pitch_cmd(float pitch_cmd)
{
	Unicode::snprintfFloat(pat_valueBuffer, PAT_VALUE_SIZE, "%.1f", pitch_cmd);
	pat_value.invalidate();
}

void UI_page2View::update_pitch(float pitch)
{
	Unicode::snprintfFloat(pitch_valueBuffer, PITCH_VALUE_SIZE, "%.1f", pitch);
	pitch_value.invalidate();
}

void UI_page2View::update_fps(float fps)
{
	Unicode::snprintfFloat(fps_valueBuffer, FPS_VALUE_SIZE, "%.0f", fps);
	fps_value.invalidate();
}
