#include <gui/ui_page2_screen/UI_page2View.hpp>
#include <gui/ui_page2_screen/UI_page2Presenter.hpp>

UI_page2Presenter::UI_page2Presenter(UI_page2View& v)
    : view(v)
{

}

void UI_page2Presenter::activate()
{

}

void UI_page2Presenter::deactivate()
{

}

void UI_page2Presenter::change_screen(uint8_t screen)
{
	/* Necessaire pour le retour page2 -> page1 : transmet la demande de
	 * changement d'ecran a la View, qui declenche l'interaction GotoScreen.
	 * (La file screen1_pres_queue n'est pas requise : Model::tick() rafraichit
	 * deja les valeurs de la page 1 a chaque tick.) */
	view.change_screen(screen);
}

void UI_page2Presenter::update_ui(volatile void* screen)
{
	volatile ui_t* ui = (volatile ui_t*) screen;

	/* Meme principe que la page 1 : Model::tick() fournit screen2 a chaque tick. */
	if (ui->tsr_value != 0) {
		float tsr_value = *(const volatile float*)ui->tsr_value;
		view.update_tsr(tsr_value);
	}
	if (ui->efficiency_value != 0) {
		float efficiency_value = *(const volatile float*)ui->efficiency_value;
		view.update_efficiency(efficiency_value);
	}
	if (ui->speed_value != 0) {
		float speed_value = *(const volatile float*)ui->speed_value;
		view.update_speed(speed_value);
	}
	if (ui->current_gear_value != 0) {
		float current_gear_value = *(const volatile float*)ui->current_gear_value;
		view.update_gear(current_gear_value);
	}
	if (ui->gear_ratio_value != 0) {
		float gear_ratio_value = *(const volatile float*)ui->gear_ratio_value;
		view.update_gear_ratio(gear_ratio_value);
	}
	if (ui->rotor_speed_value != 0) {
		float rotor_speed_value = *(const volatile float*)ui->rotor_speed_value;
		view.update_rotor_speed(rotor_speed_value);
	}
	if (ui->turb_dir_value != 0) {   // angle du mat (CAN 0x40)
		float mast_angle_value = *(const volatile float*)ui->turb_dir_value;
		view.update_mast_angle(mast_angle_value);
	}
	if (ui->wind_dir_value != 0) {
		float wind_dir_value = *(const volatile float*)ui->wind_dir_value;
		view.update_wind_dir(wind_dir_value);
	}
	if (ui->wind_speed_value != 0) {
		float wind_speed_value = *(const volatile float*)ui->wind_speed_value;
		view.update_wind_speed(wind_speed_value);
	}
	if (ui->pitch_cmd_value != 0) {
		float pitch_cmd_value = *(const volatile float*)ui->pitch_cmd_value;
		view.update_pitch_cmd(pitch_cmd_value);
	}
	if (ui->pitch_value != 0) {
		float pitch_value = *(const volatile float*)ui->pitch_value;
		view.update_pitch(pitch_value);
	}
	if (ui->fps_counter_value != 0) {
		float fps_counter_value = *(const volatile float*)ui->fps_counter_value;
		view.update_fps(fps_counter_value);
	}

	/* Ancien mecanisme par file de messages (inutilise) :
	uint8_t buf;

	if (osMessageQueueGet(screen2_pres_queue, &buf, NULL, 0) == osOK) {
		switch (buf) {
		case POWER_FLAG: {
			//float power = *(const float*)ui->data1;
			//view.update_power(power);
			break;
		}
		case EFF_FLAG: {
			//float eff = *(const float*)ui->data2;
			//view.update_efficiency(eff);
			break;
		}
		case TSR_FLAG: {
			//float tsr = *(const float*)ui->data3;
			//view.update_tsr(tsr);
			break;
		}
		default:
			break;
		}
	}*/
}
