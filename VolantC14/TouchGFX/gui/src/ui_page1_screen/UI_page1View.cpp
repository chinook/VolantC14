#include <gui/ui_page1_screen/UI_page1View.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/Application.hpp>

UI_page1View::UI_page1View()
{

}

void UI_page1View::setupScreen()
{
    UI_page1ViewBase::setupScreen();
}

void UI_page1View::tearDownScreen()
{
    UI_page1ViewBase::tearDownScreen();
}

void UI_page1View::change_screen(uint8_t screen)
{
	UI_page1ViewBase::handleKeyEvent(screen);
}

void UI_page1View::handleKeyEvent(uint8_t key)
{
#ifdef SIMULATOR
	/* Dans le simulateur PC, la barre d'espace (' ' = 32) bascule vers l'ecran 2.
	 * Guard SIMULATOR : aucun effet sur la carte. */
	if (key == ' ')
	{
		static_cast<FrontendApplication*>(touchgfx::Application::getInstance())->gotoUI_page2ScreenNoTransition();
		return;
	}
#endif
	UI_page1ViewBase::handleKeyEvent(key);
}

//TouchGFX_4_23_2_tutorial_after_generating_code_step_3 : add the function like update_change_the_name

void UI_page1View::update_turb_dir_value(float turb_dir_value_temps)
{
	Unicode::snprintfFloat(turb_dir_valueBuffer, TURB_DIR_VALUE_SIZE, "%.1f", turb_dir_value_temps);
	turb_dir_value.invalidate();
}

/* NOTE : debug_log_1..4_value et change_the_name n'ont pas de widget sur la
 * page 1 (retires dans le Designer) -> leurs fonctions restent en no-op.
 * current_gear a de nouveau un widget (gear_value, wildcard) : cable ci-dessous. */
void UI_page1View::update_current_gear_value(float current_gear_value_temps)
{
	/* Numero de vitesse (CAN 0x41, 1-14) affiche sans decimale dans gear_value. */
	Unicode::snprintfFloat(gear_valueBuffer, GEAR_VALUE_SIZE, "%.0f", current_gear_value_temps);
	gear_value.invalidate();
}

void UI_page1View::update_wind_dir_value(float wind_dir_value_temps)
{
	Unicode::snprintfFloat(wind_dir_valueBuffer, WIND_DIR_VALUE_SIZE, "%.1f", wind_dir_value_temps);
	wind_dir_value.invalidate();

	/* Aiguille de l'orientation du vent (gauge1, needle1).
	 * Mario envoie le vent dans la plage -180..+180 deg ; gauge1 est configure
	 * (Designer) avec la plage 0..180 et les angles -90..+90. On compresse donc
	 * le vent (-180..+180) sur la course de l'aiguille (-90..+90) :
	 *     valeur_gauge = vent / 2 + 90
	 *   vent = -180 -> 0   (aiguille a -90 deg)
	 *   vent =    0 -> 90  (aiguille a   0 deg)
	 *   vent = +180 -> 180 (aiguille a +90 deg)
	 * 2e arg de updateValue = duree d'animation en ticks (0 = instantane). */
	float wind_gauge = wind_dir_value_temps / 2.0f + 90.0f;
	if (wind_gauge < 0.0f)   wind_gauge = 0.0f;
	if (wind_gauge > 180.0f) wind_gauge = 180.0f;
	gauge1.updateValue((int)(wind_gauge + 0.5f), 0);
}

void UI_page1View::update_speed_value(float speed_value_temps)
{
	Unicode::snprintfFloat(speed_valueBuffer, SPEED_VALUE_SIZE, "%.2f", speed_value_temps);
	speed_value.invalidate();
}

/* NOTE (UI C14) : les widgets tsr_value, gear_ratio_value, rotor_speed_value,
 * rotor_rops_cmd_value, wind_speed_value et pitch_cmd_value ont ete retires de
 * la page 1 lors du redesign C14. Ils n'existent plus dans UI_page1ViewBase.
 * Ces fonctions sont donc en no-op pour que le projet compile. Le Presenter
 * continue de les appeler sans effet. A recabler si on recree ces widgets. */
void UI_page1View::update_tsr_value(float tsr_value_temps)
{
	(void)tsr_value_temps;
}

void UI_page1View::update_gear_ratio_value(float gear_ratio_value_temps)
{
	(void)gear_ratio_value_temps;
}

void UI_page1View::update_rotor_speed_value(float rotor_speed_value_temps)
{
	(void)rotor_speed_value_temps;
}

void UI_page1View::update_rotor_rops_cmd_value(float rotor_rops_cmd_value_temps)
{
	(void)rotor_rops_cmd_value_temps;
}

void UI_page1View::update_pitch_value(float pitch_value_temps)
{
	Unicode::snprintfFloat(pitch_valueBuffer, PITCH_VALUE_SIZE, "%.3f", pitch_value_temps);
	pitch_value.invalidate();
}

void UI_page1View::update_efficiency_value(float efficiency_value_temps)
{
	/* Affichage sans decimale (valeurs 0..150). "%.0f" arrondit a l'entier. */
	Unicode::snprintfFloat(efficiency_valueBuffer, EFFICIENCY_VALUE_SIZE, "%.0f", efficiency_value_temps);
	efficiency_value.invalidate();
}

void UI_page1View::update_wind_speed_value(float wind_speed_value_temps)
{
	/* Vitesse du vent (CAN 0x4A, calculee par ReadWeatherStation() cote Mario)
	 * affichee dans le widget wind_value de la page 1 (UI C14). */
	Unicode::snprintfFloat(wind_valueBuffer, WIND_VALUE_SIZE, "%.1f", wind_speed_value_temps);
	wind_value.invalidate();
}

void UI_page1View::update_pitch_cmd_value(float pitch_cmd_value_temps)
{
	(void)pitch_cmd_value_temps;    // widget retire (UI C14)
}

void UI_page1View::update_debug_log_1_value(float debug_log_1_value_temps)
{
	(void)debug_log_1_value_temps;
}

void UI_page1View::update_debug_log_2_value(float debug_log_2_value_temps)
{
	(void)debug_log_2_value_temps;
}

void UI_page1View::update_debug_log_3_value(float debug_log_3_value_temps)
{
	(void)debug_log_3_value_temps;
}

void UI_page1View::update_debug_log_4_value(float debug_log_4_value_temps)
{
	(void)debug_log_4_value_temps;
}

void UI_page1View::update_fps_counter_value(float fps_counter_value_temps)
{
	Unicode::snprintfFloat(fps_counter_valueBuffer, FPS_COUNTER_VALUE_SIZE, "%.0f", fps_counter_value_temps);
	fps_counter_value.invalidate();
}


void UI_page1View::update_change_the_name(float change_the_name_temps)
{
	(void)change_the_name_temps;
}
