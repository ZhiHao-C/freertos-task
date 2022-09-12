#include "FreeRTOS.h"
#include "task.h"




extern List_t pxReadyTasksLists[ configMAX_PRIORITIES ];
portCHAR flag1;
portCHAR flag2;

#define TASK1_STACK_SIZE                    20
StackType_t Task1Stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE                    20
StackType_t Task2Stack[TASK2_STACK_SIZE];

//����������
TaskHandle_t Task1_Handle;
TaskHandle_t Task2_Handle;

//����������ƿ�
TCB_t Task1TCB;
TCB_t Task2TCB;
//��������������ƿ�
TCB_t IdleTaskTCB;
//�����������ջ
StackType_t IdleTaskStack[configMINIMAL_STACK_SIZE];


void vApplicationGetIdleTaskMemory( TCB_t **ppxIdleTaskTCBBuffer, 
                                    StackType_t **ppxIdleTaskStackBuffer, 
                                    uint32_t *pulIdleTaskStackSize )
{
		*ppxIdleTaskTCBBuffer=&IdleTaskTCB;
		*ppxIdleTaskStackBuffer=IdleTaskStack; 
		*pulIdleTaskStackSize=configMINIMAL_STACK_SIZE;
}

/* �����ʱ */
void delay (uint32_t count)
{
	for(; count!=0; count--);
}


/* ����1 */
void Task1_Entry( void *p_arg )
{
	for( ;; )
	{
		flag1 = 1;
		vTaskDelay( 2 );		
		flag1 = 0;
		vTaskDelay( 2 );
	}
}


/* ����2 */
void Task2_Entry( void *p_arg )
{
	for( ;; )
	{
		flag2 = 1;
		vTaskDelay( 2 );	//����ʱΪ10ms��������Ϊ20ms	
		flag2 = 0;
		vTaskDelay( 2 );
	}
}


int main(void)
{
	prvInitialiseTaskLists();
	
//	//��������
	Task1_Handle=xTaskCreateStatic(Task1_Entry,"Task1",TASK1_STACK_SIZE,NULL,1,Task1Stack,&Task1TCB);
	Task2_Handle=xTaskCreateStatic(Task2_Entry,"Task2",TASK2_STACK_SIZE,NULL,2,Task2Stack,&Task2TCB);
	
	
//	
	//������ڵ���ӵ���Ӧ����������б�Ķ�Ӧ���ڵ���
//	vListInsertEnd( &( pxReadyTasksLists[1] ), &( ((TCB_t *)(&Task1TCB))->xStateListItem ) );
//	vListInsertEnd( &( pxReadyTasksLists[2] ), &( ((TCB_t *)(&Task2TCB))->xStateListItem ) );
	//�Լ�д��
//	vListInsertEnd(&(pxReadyTasksLists[1]),&(Task1TCB.xStateListItem));
//	vListInsertEnd(&(pxReadyTasksLists[2]),&(Task2TCB.xStateListItem));
	
	/* ��������������ʼ��������ȣ������ɹ��򲻷��� */
   vTaskStartScheduler(); 
	for(;;)
	{}
}
