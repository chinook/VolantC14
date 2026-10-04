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
	(void)screen;
	/*
	volatile ui_t* ui = (volatile ui_t*)screen;
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
