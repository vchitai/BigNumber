#include <stdio.h>
#include "Calculator.h"

void Calculator_Start()
{
	Calculator cal;
	cal.DoiSangHeDec();
	int mode = 0;

	do
	{
		printf("Calculator: Ans = \n\t");
		cal.XuatAns();
		printf("\n\n");
		printf("\t1. Nhap ans\n");
		printf("\t2. Bin\n");
		printf("\t3. Dec\n");
		printf("\t4. Hex\n");
		printf("\t5. Cong\n");
		printf("\t6. Tru\n");
		printf("\t7. Nhan\n");
		printf("\t8. Chia\n");
		printf("\t0. Off\n");
		printf("Mode = ");
		scanf("%d", &mode);

		switch (mode)
		{
		case 0: printf("\t Off\n");
			break;
		case 1: cal.NhapAns();
			break;
		case 2: cal.DoiSangHeBin();
			break;
		case 3: cal.DoiSangHeDec();
			break;
		case 4: cal.DoiSangHeHex();
			break;
		case 5: cal.Cong();
			break;
		case 6: cal.Tru();
			break;
		case 7: cal.Nhan();
			break;
		case 8: cal.Chia();
			break;
		default: printf("\t Error! Unavailable mode!\n");
			break;
		}
		printf("----------------------------\n");
	} while (mode != 0);

}