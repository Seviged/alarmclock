/*
 * buttons.c
 *
 * Created: 01.02.2017 13:41:46
 *  Author: Seviged
 */ 

 #include "buttons.h"
 #include "defines.h"
 #include "board.h"
 #include <avr/io.h>
 #include "timer.h"

 // Macros to get and set the key state without flag button pressed
 #define GET_APP_KEY_STATE(pThis)			((pThis)->nState & KEY_ST_MASK)
 #define GET_APP_KEY_EVENT(pThis)			((pThis)->nState & KEY_EV_MASK)
 #define SET_APP_KEY_STATE(pThis, nNewState)	((pThis)->nState  = ((pThis)->nState & (~KEY_ST_MASK)) | \
 (nNewState & KEY_ST_MASK))
 #define SET_APP_KEY_EVENT(pThis, nNewEvent)	((pThis)->nState  = ((pThis)->nState & (~KEY_EV_MASK)) | \
 (nNewEvent & KEY_EV_MASK))


 static KeyChannel_t m_pKeys[APP_KEY_COUNT];


 bool_t AppKey_Init()
 {
	 uint8_t nIndex;																// Index for loop

	 for (nIndex = 0; nIndex < APP_KEY_COUNT; nIndex++)							// For any channel
	 {
		 m_pKeys[nIndex].nLastTime = getTimeMs();							// Time stamp of last event
		 m_pKeys[nIndex].nState = KEY_ST_OFF;									// State of key
	 }

	 return TRUE;																// Return success
 }


 /// This function returns and clears the key event
 ///
 /// @param[in] nKeyNo key number
 /// @return event

 uint8_t AppKey_GetKeyEvent(uint8_t nKeyNo)
 {
	 uint8_t nEvent;																// The key event

	 if (nKeyNo >= APP_KEY_COUNT)												// If key no out of range
	 {
		 return FALSE;															// Return error
	 }

	 nEvent = GET_APP_KEY_EVENT(m_pKeys + nKeyNo);								// Extract the event
	 SET_APP_KEY_EVENT(m_pKeys + nKeyNo, KEY_EV_NONE);							// Clear the event
	 return nEvent;																// Return the event
 }


 /// This function checks the key state
 /// and sets the key state

 void AppKey_Process()
 {
	 uint8_t nIndex;																// Index for loop

	 for (nIndex = 0; nIndex < APP_KEY_COUNT; nIndex++)							// For any channel
	 {
		 AppKey_ProcessChannel(nIndex);											// Call state machine
	 }
 }


 /// This function processes the state machine for keys.
 /// This function has to be called periodically in main level.
 ///
 /// @param[in] nChannel current channel

 void AppKey_ProcessChannel(uint8_t nChannel)
 {
	 KeyChannel_t* pThis;														// Pointer to current channel

	 pThis = &m_pKeys[nChannel];													// Get pointer to channel

	 switch (GET_APP_KEY_STATE(pThis))											// Switch due to key state
	 {
		 case KEY_ST_OFF:														// State is off, key was up

		 if (AppKey_IsKeyPressed(nChannel))									// If key actually is pressed
		 {
			 pThis->nLastTime = getTimeMs();							// Get current time
			 SET_APP_KEY_STATE(pThis, KEY_ST_NEW);							// Set new state
		 }

		 break;

		 case KEY_ST_NEW:														// State is new pressed, key was down

		 if (AppKey_IsKeyPressed(nChannel))									// If key still is pressed
		 {
			 if (getDelayMs(pThis->nLastTime)
			 > KEY_TIME_LONG)											// If delay is enough
			 {
				 SET_APP_KEY_STATE(pThis, KEY_ST_LONG);						// Set new state
				 SET_APP_KEY_EVENT(pThis, KEY_EV_LONG);						// Set new state
			 }

		 }
		 else																// If key is released
		 {

			 if (getDelayMs(pThis->nLastTime)
			 > KEY_TIME_SHORT)											// If time is enough
			 {
				 SET_APP_KEY_EVENT(pThis, KEY_EV_SHORT);						// Set new state
			 }

			 SET_APP_KEY_STATE(pThis, KEY_ST_OFF);							// Set new state
		 }

		 break;

		 case KEY_ST_LONG:														// If state is on, key still pressed

		 if (!AppKey_IsKeyPressed(nChannel))									// If key actually is pressed
		 {
			 SET_APP_KEY_STATE (pThis, KEY_ST_OFF);							// Set new state
			 SET_APP_KEY_EVENT (pThis, KEY_EV_RELEASE);						// Release-Event-NEW
		 }
		 else
		 {
			SET_APP_KEY_STATE(pThis, KEY_ST_LONG);						// Set new state
			SET_APP_KEY_EVENT(pThis, KEY_EV_LONG);						// Set new state
		 }

		 break;

		 default:
		 pThis->nState = KEY_ST_OFF;											// Set to state OFF
		 break;
	 }

 }


 /// This function is called to retrieve
 /// the current state of a key
 ///
 /// @param[in] nChannel current channel
 /// @return TRUE, if key is pressed
 ///			FALSE if released and on error

 bool_t AppKey_IsKeyPressed(uint8_t nChannel)
 {

	 switch (nChannel)															// Switch due to channel no.
	 {
		 case 0:																	// Case: Channel #0
		 return IS_KEY_PRESSED_0;											// Return key state

		 case 1:																	// Case: Channel #1
		 return IS_KEY_PRESSED_1;											// Return key state

		 default:																// On any other value
		 return FALSE;														// Return error
	 }

 }