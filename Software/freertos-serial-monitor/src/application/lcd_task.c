/**
 ******************************************************************************
 * @file	lcd_task.c
 * @author	Hampus Sandberg
 * @version	0.1
 * @date	2014-09-07
 * @brief
 ******************************************************************************
	Copyright (c) 2014 Hampus Sandberg.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation, either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "lcd_task.h"

#include "simple_gui.h"
#include "simple_gui_config.h"
#include "ft5206.h"

/* Private defines -----------------------------------------------------------*/
#define GUI_BLUE	0x237F
#define GUI_RED		0xF926
#define GUI_GREEN	0x362A
#define GUI_YELLOW	0xFEE6
#define GUI_PURPLE	0xA8D6
#define GUI_GRAY	0xB596
#define GUI_MAGENTA	0xF81F
#define GUI_CYAN	0x07FF
#define GUI_DARK_BLUE	0x11CE

/* Private typedefs ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void prvHardwareInit();

static void guiTestInit();
static void guiTest2Init();
static void guiTest();
static void guiTest2();

/* Functions -----------------------------------------------------------------*/
/**
 * @brief	The main task for the LCD
 * @param	pvParameters:
 * @retval	None
 */
void lcdTask(void *pvParameters)
{
	prvHardwareInit();
//	guiTestInit();
	guiTest2Init();

	xLCDEventQueue = xQueueCreate(10, sizeof(LCDEventMessage));
	if (xLCDEventQueue == 0)
	{
		// Queue was not created and must not be used.
	}

	/* The parameter in vTaskDelayUntil is the absolute time
	 * in ticks at which you want to be woken calculated as
	 * an increment from the time you were last woken. */
	TickType_t xNextWakeTime;
	/* Initialize xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	while (1)
	{
//		vTaskDelayUntil(&xNextWakeTime, 1000 / portTICK_PERIOD_MS);
//		guiTest();
		guiTest2();
	}
}


/* Private functions .--------------------------------------------------------*/
/**
 * @brief	Initializes the hardware
 * @param	None
 * @retval	None
 */
static void prvHardwareInit()
{
	/* LCD */
	LCD_Init();

	/* Capacitive Touch */
	FT5206_Init();
}

static void guiTestInit()
{
	GUI_Init();

	LCD_SetBackgroundColor(LCD_COLOR_BLACK);
	LCD_ClearFullWindow();

	GUIButton button;
	button.disabledBackgroundColor = LCD_COLOR_BLACK;
	button.pressedBackgroundColor = LCD_COLOR_WHITE;
	button.enabledTextColor = LCD_COLOR_WHITE;
	button.object.borderColor = LCD_COLOR_WHITE;
	button.object.borderThickness = 1;
	button.state = GUIButtonState_Enabled;

	button.object.yPos = 0;
	button.object.height = 50;
	button.object.layer = GUILayer_0;
	button.object.displayState = GUIDisplayState_NotHidden;

	/* CAN1 Button */
	button.object.id = guiConfigCAN1_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_BLUE;
	button.text = "CAN1";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 0;
	button.object.width = 100;
	button.object.border = GUIBorder_Bottom | GUIBorder_Right;
	GUI_AddButton(&button);

	/* CAN2 Button */
	button.object.id = guiConfigCAN2_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_RED;
	button.text = "CAN2";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 100;
	button.object.border = GUIBorder_Bottom | GUIBorder_Right | GUIBorder_Left;
	GUI_AddButton(&button);

	/* UART1 Button */
	button.object.id = guiConfigUART1_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_GREEN;
	button.text = "UART1";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 200;
	GUI_AddButton(&button);

	/* UART2 Button */
	button.object.id = guiConfigUART2_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_YELLOW;
	button.text = "UART2";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 300;
	GUI_AddButton(&button);

	/* RS232 Button */
	button.object.id = guiConfigRS232_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_PURPLE;
	button.text = "RS232";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 400;
	GUI_AddButton(&button);

	/* I2C Button */
	button.object.id = guiConfigI2C_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_GRAY;
	button.text = "I2C";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 500;
	GUI_AddButton(&button);

	/* ADC Button */
	button.object.id = guiConfigADC_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_MAGENTA;
	button.text = "ADC";
	button.textSize = LCDFontEnlarge_1x;
	button.object.xPos = 600;
	button.object.yPos = 0;
	button.object.width = 50;
	button.object.height = 25;
	button.object.border = GUIBorder_Right | GUIBorder_Left;
	GUI_AddButton(&button);

	/* GPIO Button */
	button.object.id = guiConfigGPIO_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_CYAN;
	button.text = "GPIO";
	button.textSize = LCDFontEnlarge_1x;
	button.object.yPos = 25;
	button.object.height = 25;
	button.object.border = GUIBorder_Bottom | GUIBorder_Right | GUIBorder_Left;
	GUI_AddButton(&button);

	/* Settings Button */
	button.object.id = guiConfigSETTINGS_BUTTON_ID;
	button.disabledBackgroundColor = button.enabledBackgroundColor = button.pressedTextColor = GUI_DARK_BLUE;
	button.disabledTextColor = LCD_COLOR_WHITE;
	button.text = "Settings";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 650;
	button.object.yPos = 430;
	button.object.width = 150;
	button.object.height = 50;
	button.object.border = GUIBorder_Top | GUIBorder_Left;
	GUI_AddButton(&button);

	/* Storage Button */
	button.object.id = guiConfigSTORAGE_BUTTON_ID;
	button.disabledBackgroundColor = button.enabledBackgroundColor = button.pressedTextColor = GUI_DARK_BLUE;
	button.disabledTextColor = LCD_COLOR_WHITE;
	button.text = "Storage";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 650;
	button.object.yPos = 380;
	button.object.width = 150;
	button.object.height = 50;
	button.object.border = GUIBorder_Top | GUIBorder_Bottom | GUIBorder_Left;
	GUI_AddButton(&button);

	GUI_DrawAllButtons();

//	LCD_SetForegroundColor(LCD_COLOR_RED);
//	LCD_DrawSquareOrLine(0, 799, 50, 50, LINE, FILLED);
}

void testCallback(GUITouchEvent Event)
{
	GUI_ClearTextBox(guiConfigMAIN_TEXT_BOX_ID);
}

static void guiTest2Init()
{
	GUI_Init();

	/* TODO: BUG? We need to clear the active window one time first for some reason */
	LCD_ClearActiveWindow(0, 0, 0, 0);

	GUITextBox textBox;

	/* Main text box */
	textBox.object.id = guiConfigMAIN_TEXT_BOX_ID;
	textBox.object.xPos = 0;
	textBox.object.yPos = 50;
	textBox.object.width = 650;
	textBox.object.height = 430;
	textBox.object.layer = GUILayer_0;
	textBox.object.displayState = GUIDisplayState_NotHidden;
	textBox.object.border = GUIBorder_Top | GUIBorder_Right;
	textBox.object.borderThickness = 1;
	textBox.object.borderColor = LCD_COLOR_WHITE;
	textBox.textSize = LCDFontEnlarge_1x;
	textBox.xWritePos = 0;
	textBox.yWritePos = 0;
	GUI_AddTextBox(&textBox);

	/* Temperature Text Box */
	textBox.object.id = guiConfigTEMP_TEXT_BOX_ID;
	textBox.object.xPos = 650;
	textBox.object.yPos = 25;
	textBox.object.width = 150;
	textBox.object.height = 25;
	textBox.object.layer = GUILayer_0;
	textBox.object.displayState = GUIDisplayState_NotHidden;
	textBox.object.border = GUIBorder_Left | GUIBorder_Bottom;
	textBox.object.borderThickness = 1;
	textBox.object.borderColor = LCD_COLOR_WHITE;
	textBox.textSize = LCDFontEnlarge_1x;
	textBox.xWritePos = 100;
	textBox.yWritePos = 3;
	GUI_AddTextBox(&textBox);

	/* Debug Text Box */
	textBox.object.id = guiConfigDEBUG_TEXT_BOX_ID;
	textBox.object.xPos = 650;
	textBox.object.yPos = 300;
	textBox.object.width = 150;
	textBox.object.height = 100;
	textBox.object.layer = GUILayer_0;
	textBox.object.displayState = GUIDisplayState_NotHidden;
	textBox.object.border = GUIBorder_NoBorder;
	textBox.object.borderThickness = 0;
	textBox.object.borderColor = LCD_COLOR_WHITE;
	textBox.textSize = LCDFontEnlarge_1x;
	textBox.xWritePos = 0;
	textBox.yWritePos = 0;
	GUI_AddTextBox(&textBox);

	GUI_DrawTextBox(guiConfigMAIN_TEXT_BOX_ID);
	GUI_DrawTextBox(guiConfigTEMP_TEXT_BOX_ID);
	GUI_DrawTextBox(guiConfigDEBUG_TEXT_BOX_ID);

	GUI_WriteStringInTextBox(guiConfigTEMP_TEXT_BOX_ID, "20 C");
	GUI_WriteStringInTextBox(guiConfigMAIN_TEXT_BOX_ID, "Hello World!");



	GUIButton button;
	button.disabledBackgroundColor = LCD_COLOR_BLACK;
	button.pressedBackgroundColor = LCD_COLOR_WHITE;
	button.enabledTextColor = LCD_COLOR_WHITE;
	button.object.borderColor = LCD_COLOR_WHITE;
	button.object.borderThickness = 1;
	button.state = GUIButtonState_Enabled;

	button.object.yPos = 0;
	button.object.height = 50;
	button.object.layer = GUILayer_0;
	button.object.displayState = GUIDisplayState_NotHidden;

	/* CAN1 Button */
	button.object.id = guiConfigCAN1_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_BLUE;
	button.text = "CAN1";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 0;
	button.object.width = 100;
	button.object.border = GUIBorder_Bottom | GUIBorder_Right;
	button.touchCallback = testCallback;
	GUI_AddButton(&button);

	/* CAN2 Button */
	button.object.id = guiConfigCAN2_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_RED;
	button.text = "CAN2";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 100;
	button.object.border = GUIBorder_Bottom | GUIBorder_Right | GUIBorder_Left;
	button.touchCallback = 0;
	GUI_AddButton(&button);

	/* UART1 Button */
	button.object.id = guiConfigUART1_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_GREEN;
	button.text = "UART1";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 200;
	button.touchCallback = 0;
	GUI_AddButton(&button);

	/* UART2 Button */
	button.object.id = guiConfigUART2_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_YELLOW;
	button.text = "UART2";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 300;
	button.touchCallback = 0;
	GUI_AddButton(&button);

	/* RS232 Button */
	button.object.id = guiConfigRS232_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_PURPLE;
	button.text = "RS232";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 400;
	button.touchCallback = 0;
	GUI_AddButton(&button);

	/* I2C Button */
	button.object.id = guiConfigI2C_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_GRAY;
	button.text = "I2C";
	button.textSize = LCDFontEnlarge_2x;
	button.object.xPos = 500;
	button.touchCallback = 0;
	GUI_AddButton(&button);

	/* ADC Button */
	button.object.id = guiConfigADC_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_MAGENTA;
	button.text = "ADC";
	button.textSize = LCDFontEnlarge_1x;
	button.object.xPos = 600;
	button.object.yPos = 0;
	button.object.width = 50;
	button.object.height = 25;
	button.object.border = GUIBorder_Right | GUIBorder_Left;
	button.touchCallback = 0;
	GUI_AddButton(&button);

	/* GPIO Button */
	button.object.id = guiConfigGPIO_BUTTON_ID;
	button.enabledBackgroundColor = button.disabledTextColor = button.pressedTextColor = GUI_CYAN;
	button.text = "GPIO";
	button.textSize = LCDFontEnlarge_1x;
	button.object.yPos = 25;
	button.object.height = 25;
	button.object.border = GUIBorder_Bottom | GUIBorder_Right | GUIBorder_Left;
	button.touchCallback = 0;
	GUI_AddButton(&button);

	GUI_DrawAllButtons();
}

static void guiTest()
{
	static uint32_t index = 0;
	static uint32_t state = GUIButtonState_Enabled;

	GUI_SetButtonState(index, state);

	index++;
	if (index >= guiConfigNUMBER_OF_BUTTONS)
	{
		index = 0;
		state++;
		if (state > GUIButtonState_TouchUp)
			state = 0;
	}

	vTaskDelay(1000 / portTICK_PERIOD_MS);
}

FT5206TouchCoordinate prvCoordinate;
FT5206Event prvEvent;

static void guiTest2()
{
	static TickType_t xNextWakeTime = 0;

	LCDEventMessage receivedMessage;
	if (xQueueReceive(xLCDEventQueue, &receivedMessage, 50) == pdTRUE)
	{
		/* Item sucessfully removed from the queue */

		switch (receivedMessage.event)
		{
			case LCDEvent_TouchEvent:
				if (receivedMessage.data[3] == FT5206Point_1)
				{
					GUI_ClearTextBox(guiConfigDEBUG_TEXT_BOX_ID);
					GUI_SetWritePosition(guiConfigDEBUG_TEXT_BOX_ID, 5, 0);
					GUI_WriteStringInTextBox(guiConfigDEBUG_TEXT_BOX_ID, "X:");
					GUI_WriteNumberInTextBox(guiConfigDEBUG_TEXT_BOX_ID, receivedMessage.data[0]);
					GUI_WriteStringInTextBox(guiConfigDEBUG_TEXT_BOX_ID, ", Y:");
					GUI_WriteNumberInTextBox(guiConfigDEBUG_TEXT_BOX_ID, receivedMessage.data[1]);
					GUI_SetWritePosition(guiConfigDEBUG_TEXT_BOX_ID, 5, 16);
					GUI_WriteStringInTextBox(guiConfigDEBUG_TEXT_BOX_ID, "EVENT:");
					GUI_WriteNumberInTextBox(guiConfigDEBUG_TEXT_BOX_ID, receivedMessage.data[2]);

					LCD_SetForegroundColor(LCD_COLOR_GREEN);
					LCD_DrawCircle(receivedMessage.data[0], receivedMessage.data[1], 2, 1);

					GUITouchEvent touchEvent;
					if (receivedMessage.data[2] == FT5206Event_PutUp)
						touchEvent = GUITouchEvent_Up;
					else if (receivedMessage.data[2] == FT5206Event_PutDown)
						touchEvent = GUITouchEvent_Down;
					GUI_CheckAllNonHiddenButtonsForTouchEventAt(touchEvent, receivedMessage.data[0], receivedMessage.data[1]);
				}
				else if (receivedMessage.data[3] == FT5206Point_2)
				{
					LCD_SetForegroundColor(LCD_COLOR_BLUE);
					LCD_DrawCircle(receivedMessage.data[0], receivedMessage.data[1], 2, 1);
				}
				else if (receivedMessage.data[3] == FT5206Point_3)
				{
					LCD_SetForegroundColor(LCD_COLOR_RED);
					LCD_DrawCircle(receivedMessage.data[0], receivedMessage.data[1], 2, 1);
				}
				else if (receivedMessage.data[3] == FT5206Point_4)
				{
					LCD_SetForegroundColor(LCD_COLOR_YELLOW);
					LCD_DrawCircle(receivedMessage.data[0], receivedMessage.data[1], 2, 1);
				}
				else if (receivedMessage.data[3] == FT5206Point_5)
				{
					LCD_SetForegroundColor(LCD_COLOR_WHITE);
					LCD_DrawCircle(receivedMessage.data[0], receivedMessage.data[1], 2, 1);
				}
				break;
			default:
				break;
		}
	}
	else
	{
//		vTaskDelayUntil(&xNextWakeTime, 100 / portTICK_PERIOD_MS);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
	}
}

/* Interrupt Handlers --------------------------------------------------------*/
