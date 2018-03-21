#include<stdio.h>

int main()
{
	int i, total_logical_memory, frame_size, total_phy_memory, num_pages, num_of_frames;
	printf("Enter the total logical memory\n");
	scanf("%d", &total_logical_memory);

	printf("Enter the total physical memory\n");
	scanf("%d", &total_phy_memory);

	printf("Enter the sixe of one page\n");
	scanf("%d", &frame_size);

	num_pages = total_logical_memory/frame_size;
	num_of_frames = total_phy_memory/frame_size;
	int page_table[num_pages];
	
	int temp;


	for(i=0;i<num_pages;++i)
	{
		while(1)
		{
			printf("Enter the frame number for page number-%d\n", i);
			scanf("%d", &temp);

			if(temp >= num_of_frames)
			{
				printf("Invalid frame number\nRenter the value\n");
				continue;
			}
			break;
			
		}
		page_table[i] = temp;
	}

	int logic_add;
	
	while(1)
	{
		printf("Enter the logical address\n");
		scanf("%d", &logic_add);

		if(logic_add < 0 || logic_add > total_logical_memory)
		{
			printf("Invalid logical address\n");
			continue;
		}

		int page_no = logic_add/frame_size;
		if(page_table[page_no] < 0)
		{
			printf("Page Fault. The page does not exist\n");
			continue;
		}

		int offset = logic_add%frame_size;
		// int j;
		// for(j=0;j<num_of_frames;++j)
		// {
		// 	if(page_table[j] == page_no)
		// 		break;
		// }
		printf("Physical Address of %d is %d\n", logic_add, page_table[page_no] * frame_size + offset);
	}

}