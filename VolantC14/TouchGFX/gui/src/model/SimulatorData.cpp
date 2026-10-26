/*
 * SimulatorData.cpp
 *
 * Fichier compile UNIQUEMENT pour le simulateur PC (garde #ifdef SIMULATOR).
 *
 * Sur la cible STM32, les globals screen1 / screen2 / desired_screen /
 * active_screen_index et les valeurs derriere les pointeurs de ui_t sont
 * fournis par screen_tasks.c (rempli par le CAN). Ce fichier-la n'est pas
 * compile sur PC : on recree donc ici des definitions minimales + des valeurs
 * de test pour que le simulateur puisse tourner et qu'on voie l'UI bouger.
 *
 * Ne touche pas au comportement sur la carte (tout est sous #ifdef SIMULATOR).
 */
#ifdef SIMULATOR

#include <stdint.h>
#include <stdlib.h>

extern "C" {
	#include "..\..\..\..\STM32CubeIDE\Application\User\application\ui.h"
}

/* Globals normalement definis dans screen_tasks.c (cible). */
volatile ui_t   screen1;
volatile ui_t   screen2;
volatile uint8_t desired_screen      = 0;
volatile uint8_t active_screen_index = 0;

/* Valeurs de test placees derriere les pointeurs de screen1/screen2. */
static float sim_turb_dir       = 0.0f;
static float sim_current_gear   = 7.0f;
static float sim_wind_dir       = 0.0f;   /* balaye -180..+180 (voir plus bas) */
static float sim_speed          = 12.3f;
static float sim_tsr            = 2.5f;
static float sim_gear_ratio     = 1.8f;
static float sim_rotor_speed    = 320.0f;
static float sim_rotor_rops_cmd = 300.0f;
static float sim_pitch          = 0.0f;
static float sim_efficiency     = 0.42f;
static float sim_wind_speed     = 8.5f;
static float sim_pitch_cmd      = 0.0f;
static float sim_debug_log_1    = 0.0f;
static float sim_debug_log_2    = 0.0f;
static float sim_debug_log_3    = 0.0f;
static float sim_debug_log_4    = 0.0f;
static float sim_fps_counter    = 60.0f;
static float sim_change_the_name= 0.0f;

static void sim_wire_pointers(volatile ui_t* s)
{
	s->turb_dir_value       = &sim_turb_dir;
	s->current_gear_value   = &sim_current_gear;
	s->wind_dir_value       = &sim_wind_dir;
	s->speed_value          = &sim_speed;
	s->tsr_value            = &sim_tsr;
	s->gear_ratio_value     = &sim_gear_ratio;
	s->rotor_speed_value    = &sim_rotor_speed;
	s->rotor_rops_cmd_value = &sim_rotor_rops_cmd;
	s->pitch_value          = &sim_pitch;
	s->efficiency_value     = &sim_efficiency;
	s->wind_speed_value     = &sim_wind_speed;
	s->pitch_cmd_value      = &sim_pitch_cmd;
	s->debug_log_1_value    = &sim_debug_log_1;
	s->debug_log_2_value    = &sim_debug_log_2;
	s->debug_log_3_value    = &sim_debug_log_3;
	s->debug_log_4_value    = &sim_debug_log_4;
	s->fps_counter_value    = &sim_fps_counter;
	s->change_the_name      = &sim_change_the_name;
}

/* Appele a chaque tick par Model::tick() (uniquement en simulateur). */
void simulator_feed_screens(void);

void simulator_feed_screens(void)
{
	static bool wired = false;
	if (!wired) {
		sim_wire_pointers(&screen1);
		sim_wire_pointers(&screen2);
		wired = true;
	}

	/* Vent : une direction cible aleatoire (-180..+180 deg) est tiree toutes les
	 * 3 a 6 s ; le vent s'en approche en douceur, ce qui fait bouger l'aiguille
	 * du vent (gauge1).
	 * Mat : il rejoint la direction du vent avec un retard (filtre du 1er ordre,
	 * ~1 s a 60 ticks/s), ce qui fait suivre l'aiguille du mat (gauge2) a celle du
	 * vent. Parametres : WIND_EASE (vent), MAST_EASE (retard du mat, plus petit =
	 * plus de retard). */
	static const float WIND_EASE = 0.05f;
	static const float MAST_EASE = 0.02f;
	static float wind_target = 0.0f;
	static int   ticks_before_new_target = 0;

	if (ticks_before_new_target <= 0) {
		wind_target = (float)(rand() % 361) - 180.0f;       /* -180..+180 */
		ticks_before_new_target = 180 + rand() % 181;       /* 3..6 s */
	}
	ticks_before_new_target--;

	sim_wind_dir += (wind_target - sim_wind_dir) * WIND_EASE;
	sim_turb_dir += (sim_wind_dir - sim_turb_dir) * MAST_EASE;
}

#endif /* SIMULATOR */
