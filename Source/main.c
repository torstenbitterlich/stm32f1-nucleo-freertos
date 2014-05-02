/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "task.h"

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F0-Discovery_Demo
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;

void
prvSetupHardware(void)
{
    /* Configure LED2 on STM32F1-Nucleo */
    STM_EVAL_LEDInit(LED2);

    /* Initialize User_Button on STM32F0-Discovery */
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
}

void
blinkyTask(void *dummy)
{
    (void)dummy;

    /* Initiate Blink Speed variable */
    uint8_t BlinkSpeed = 1;

    while (1) {
        /* Check if the user button is pressed */
        if (STM_EVAL_PBGetState(BUTTON_USER)== SET) {
            /* BlinkSpeed: 1 -> 2 -> 0, then re-cycle */

            /* Increment the blink speed counter */
            BlinkSpeed++;

            /* Default value for blink speed counter */
            if (BlinkSpeed == 3) {
                BlinkSpeed = 0;
            }
        }

        /* Test on blink speed */
        if (BlinkSpeed == 2) {
            /* LED2 toggles each 100 ms */
            STM_EVAL_LEDToggle(LED2);

            /* maintain LED2 status for 100ms */
            vTaskDelay(100);
        } else if (BlinkSpeed == 1) {
            /* LED3 toggles each 200 ms */
            STM_EVAL_LEDToggle(LED2);

            /* maintain LED2 status for 200ms */
            vTaskDelay(200);
        } else {
            /* LED3 Off */
            STM_EVAL_LEDOff(LED2);
        }
    }
}

void
vTaskInit(void)
{
    xTaskCreate(blinkyTask,
                (const signed char *)"blinkyTask",
                configMINIMAL_STACK_SIZE,
                NULL,                 /* pvParameters */
                tskIDLE_PRIORITY + 1, /* uxPriority */
                NULL                  /* pvCreatedTask */);
}

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int
main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
     * this is done through SystemInit() function which is called from startup
     * file (startup_stm32f2xx_xx.s) before to branch to application main.
     * To reconfigure the default setting of SystemInit() function, refer to
     * system_stm32f2xx.c file */
    prvSetupHardware();

    vTaskInit();

    vTaskStartScheduler();

    return (0);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void
assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    (void)file;
    (void)line;

    /* Infinite loop */
    while (1) {
    }
}

#endif /* ifdef  USE_FULL_ASSERT */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
