/* add user code begin Header */
/**
  **************************************************************************
  * @file     wk_tmr.c
  * @brief    work bench config program
  **************************************************************************
  * Copyright (c) 2025, Artery Technology, All rights reserved.
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */
/* add user code end Header */

/* Includes ------------------------------------------------------------------*/
#include "wk_tmr.h"

/* add user code begin 0 */

/* add user code end 0 */

/**
  * @brief  init tmr7 function.
  * @param  none
  * @retval none
  */
void wk_tmr7_init(void)
{
  /* add user code begin tmr7_init 0 */

  /* add user code end tmr7_init 0 */

  /* add user code begin tmr7_init 1 */

  /* add user code end tmr7_init 1 */

  /* configure counter settings */
  tmr_cnt_dir_set(TMR7, TMR_COUNT_UP);
  tmr_period_buffer_enable(TMR7, TRUE);
  tmr_base_init(TMR7, 2000, 42);

  /* configure primary mode settings */
  tmr_primary_mode_select(TMR7, TMR_PRIMARY_SEL_RESET);

  tmr_counter_enable(TMR7, TRUE);

  /* enable ovfien interrupt */
  tmr_interrupt_enable(TMR7, TMR_OVF_INT, TRUE);

  /* add user code begin tmr7_init 2 */

  /* add user code end tmr7_init 2 */
}

/* add user code begin 1 */

/* add user code end 1 */
