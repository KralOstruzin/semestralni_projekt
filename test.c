#define FAST_SPIN_PIN (4)// E4
#define HEAT_PIN (1) // E3

void init(void);
static inline int IsKeyPressed(int pin);

void zapnuti_topeni30();
void zapnuti_topeni40();
void zapnuti_vody50();
void zapnuti_vody100();
void zapnuti_topeni60();
void zapnuti_topeni90();
void otaceni_vpravo5();
void otaceni_vlevo5();
void suseni();
void vypusteni();
void prani1();


int main(void) {

init();
SYSTICK_initialize();



while (!IsKeyPressed(SWITCH_PIN))

suseni();
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
}
void prani1()
{
	static enum {
			ZACATEK,
			NAPOUSTENI_50,
			OHREV_40,
			SPIN_RIGTH,
			SPIN_LEFT,
			SUSENI,
			VYPUSTENI,
		}

		stav = ZACATEK;
		switch (stav) {
		case ZACATEK:
			stav = NAPOUSTENI_50;
			break;

		case NAPOUSTENI_50:

			zapnuti_vody50();
			stav = OHREV_40;
			break;
		case OHREV_40:

			zapnuti_topeni40();
			stav = SPIN_RIGTH;
			break;

		case SPIN_RIGTH:
			otaceni_vpravo5();
			stav = SPIN_LEFT;
			break;
		case SPIN_LEFT:
			otaceni_vlevo5();
			stav = VYPUSTENI;
			break;
		case SUSENI:
			suseni();
			break;
		case VYPUSTENI:
			vypusteni();
			stav = SUSENI;
			break;
		default:
			break;
		}
}


void vypusteni()
{
PTD->PSOR = (1 << H2O_OUT_PIN);
SYSTICK_delay_ms(10000);
PTD->PCOR = (1 << H2O_OUT_PIN);
}
void suseni()
{

PTE ->PSOR = (1 << FAST_SPIN_PIN);
PTE ->PSOR = (1 << SPIN_RIGHT_PIN);
SYSTICK_delay_ms(5000);
PTE ->PCOR = (1 << SPIN_RIGHT_PIN);
PTE ->PCOR = (1 << FAST_SPIN_PIN);

}
void otaceni_vpravo5()
{
PTE ->PSOR = (1 << SPIN_RIGHT_PIN);
SYSTICK_delay_ms(5000);
PTE ->PCOR = (1 << SPIN_RIGHT_PIN);
}
void otaceni_vlevo5()
{
PTC ->PSOR = (1 << SPIN_LEFT_PIN);
SYSTICK_delay_ms(5000);
PTC ->PCOR = (1 << SPIN_LEFT_PIN);
}

void zapnuti_vody50(){
PTE ->PSOR = (1 << H2O_IN_PIN);

while ((PTC->PDIR & (1 << LEVEL50_PIN)) == 0);

PTE ->PCOR = (1 << H2O_IN_PIN);
}

void zapnuti_vody100(){
PTE ->PSOR = (1 << H2O_IN_PIN);

while ((PTD->PDIR & (1 << LEVEL100_PIN)) == 0);

PTE ->PCOR = (1 << H2O_IN_PIN);
}

void zapnuti_topeni30(){
PTE ->PSOR = (1 << HEAT_PIN);

while ((PTD->PDIR & (1 << TEMP30_PIN)) == 0);

PTE ->PCOR = (1 << HEAT_PIN);
}

void zapnuti_topeni40(){
PTE ->PSOR = (1 << HEAT_PIN);

while ((PTC->PDIR & (1 << TEMP40_PIN)) == 0);

PTE ->PCOR = (1 << HEAT_PIN);
}

void zapnuti_topeni60(){
PTE ->PSOR = (1 << HEAT_PIN);

while ((PTD->PDIR & (1 << TEMP60_PIN)) == 0);

PTE ->PCOR = (1 << HEAT_PIN);
}

void zapnuti_topeni90(){
PTE ->PSOR = (1 << HEAT_PIN);

while ((PTC->PDIR & (1 << TEMP90_PIN)) == 0);

PTE ->PCOR = (1 << HEAT_PIN);
}




void init(void)
{

// Enable clock for ports A, B, C, D, E
SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK |
SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK );
// Set pin function to GPIO

PORTA->PCR[SWITCH_PIN] = PORT_PCR_MUX(1);

PORTE->PCR[H2O_IN_PIN] = PORT_PCR_MUX(1);
PORTE->PCR[SPIN_RIGHT_PIN] = PORT_PCR_MUX(1);
PORTE->PCR[FAST_SPIN_PIN] = PORT_PCR_MUX(1);
PORTE->PCR[HEAT_PIN] = PORT_PCR_MUX(1);

PORTD->PCR[TEMP30_PIN] = PORT_PCR_MUX(1);
PORTD->PCR[TEMP60_PIN] = PORT_PCR_MUX(1);
PORTD->PCR[LEVEL100_PIN] = PORT_PCR_MUX(1);
PORTD->PCR[H2O_OUT_PIN] = PORT_PCR_MUX(1);

PORTC->PCR[TEMP40_PIN] = PORT_PCR_MUX(1);
PORTC->PCR[TEMP90_PIN] = PORT_PCR_MUX(1);
PORTC->PCR[LEVEL50_PIN] = PORT_PCR_MUX(1);
PORTC->PCR[SPIN_LEFT_PIN] = PORT_PCR_MUX(1);


PTE->PDDR |= (1 << H2O_IN_PIN);
PTD->PDDR |= (1 << H2O_OUT_PIN);
PTC->PDDR |= (1 << SPIN_LEFT_PIN);
PTE->PDDR |= (1 << SPIN_RIGHT_PIN);
PTE->PDDR |= (1 << FAST_SPIN_PIN);
PTE->PDDR |= (1 << HEAT_PIN);


PTA->PDDR &= ~(1 << SWITCH_PIN);
PTD->PDDR &= ~(1 << TEMP30_PIN);
PTC->PDDR &= ~(1 << TEMP40_PIN);
PTD->PDDR &= ~(1 << TEMP60_PIN);
PTC->PDDR &= ~(1 << TEMP90_PIN);
PTC->PDDR &= ~(1 << LEVEL50_PIN);
PTD->PDDR &= ~(1 << LEVEL100_PIN);
}
/* Return 1 if the switch on given pin is pressed, 0 if not pressed.
 * */
static inline int IsKeyPressed(int pin) {
if ((PTA->PDIR & (1 << pin)) == 0)
return 1;
else
return 0;
}
/*void delay(int duration)
{
unsigned long n = 30000L;
while ( n-- );
}
*/

