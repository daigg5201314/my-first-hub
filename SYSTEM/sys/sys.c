#include "sys.h"



void NVIC_Configuration(nvic_conf_e priority)
{
	switch (priority)
	{
	case PRIORITY_0:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		break;
	case PRIORITY_1:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		break;
	case PRIORITY_2:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		break;
	case PRIORITY_3:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
		break;
	case PRIORITY_4:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		break;
	}
}
