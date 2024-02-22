#include <stdio.h>
#include <string.h>

int main()
{
int proces, resources;
proces = 5; 
resources = 5; 
int alloc[5][5];// Allocation Matrix

FILE *file = fopen("allocations.txt", "r");
   for (int i = 0; i < proces; ++i) {
        for (int j = 0; j < resources; ++j) {
            if (fscanf(file, "%d", &alloc[i][j]) != 1) {
                fclose(file);
                return 1;
            }
        }
    }

fclose(file);

	int sum[5] = {0}; 
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			sum[j] += alloc[i][j];
		}
	}

// need Matrix
int need[5][5] ;

FILE* file3 = fopen("requests.txt", "r");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (fscanf(file3, "%d", &need[i][j]) != 1) {
                fclose(file3);
                return 1;
            }
        }
    }
    fclose(file3);

int max[5] ;//available
FILE* file2 = fopen("resources.txt", "r");

for (int i = 0; i < 5; ++i) {
    if (fscanf(file, "%d", &max[i]) != 1) {
        fclose(file);
        return 1;
    }
}
fclose(file2);

for (int i = 0; i < 5; i++) {
	max[i] -= sum[i];}

int states[proces];
int ans[proces];
int ptr = 0;
for (int k = 0; k < proces; k++) {
	states[k] = 0;
}

int y = 0;
for (int k = 0; k < 5; k++) {
	for (int i = 0; i < proces; i++) {
		if (states[i] == 0) {
			int flag = 0;
			for (int j = 0; j < resources; j++) {
				if (need[i][j] > max[j]){
					flag = 1;
					break;
				}
			}
		if (flag == 0) {
			ans[ptr++] = i;
			for (y = 0; y < resources; y++)
				max[y] += alloc[i][y];
			states[i] = 1;
		}
	}
}
}
int flag = 1;
int counter = 0;

for (int i = 0; i < proces; i++) {
if (states[i] == 0) {
    flag = 0;
    int deadlockFlag = 0;
    for (int j = 0; j < resources; j++) {
        if (need[i][j] > max[j]) {
            deadlockFlag = 1;
            break;
        }
    }
        if (deadlockFlag == 1) {
    counter++;
        }
    }
}

  for (int i = 0; i < proces; i++)
    {
        printf("Process: P%d\n", i + 1);
        printf("Allocated resources: ");
        for (int j = 0; j < resources; j++)
        {
            printf("R%d:%d ", j + 1, alloc[i][j]);
        }
        printf("\n");
        printf("Resource request: ");
        for (int j = 0; j < resources; j++)
        {
            printf("R%d:%d ", j + 1, need[i][j]);
        }
        printf("\n\n");
    }



if (counter > 0)
{
    printf("The following processes are in a deadlock state: ");
    for (int i = 0; i < proces; i++)
    {
        if (states[i] == 0)
        {
            printf("P%d ", i+1);
        }
    }
    printf("\n");
    printf("Running order for process: ");
    for (int i = 0; i < ptr - 1; i++)
        printf(" P%d ->", ans[i]+1);
    printf(" P%d\n", ans[ptr - 1]+1);
}

if (flag == 1) {
    printf("Running order for process: ");
    for (int i = 0; i < proces - 1; i++)
        printf(" P%d ->", ans[i]);
    printf(" P%d", ans[proces - 1]);
}
	return (0);
}
