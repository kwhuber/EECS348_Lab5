#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function to calculate the average of an array of sales data */
double calculateAverage(double sales[], int numMonths) {
    double sum = 0.0;
    for (int i = 0; i < numMonths; i++) {
        sum += sales[i];
    }
    return sum / numMonths;
}

/* Data structure to hold month name and sales data. */
struct MonthlySalesData {
    char monthName[20];
    double sales;
};

/* Function to sort the sales data from highest to lowest. */
void sortSalesDataHighToLow(struct MonthlySalesData data[], int numMonths) {
    for (int i = 0; i < numMonths - 1; i++) {
        for (int j = 0; j < numMonths - i - 1; j++) {
            if (data[j].sales < data[j + 1].sales) {
                struct MonthlySalesData temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

/* The function that is called when program is executed. */
int main() {
    FILE *file;
    file = fopen("sales_problem.txt", "r");

    double monthlySales[12];
    double sixMonthMovingAverage[12];
    double minSales, maxSales, avgSales;

    /* Month names. */
    const char *monthNames[] = {
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
    };

    /* Reads monthly sales data from the input file. */
    for (int i = 0; i < 12; i++) {
        if (fscanf(file, "%lf", &monthlySales[i]) != 1) {
            printf("Error reading sales data from the file.\n");
            return 1;
        }
    }
 
    /* Print the monthly sales report. */
	printf("------------------------------------");
    printf("\nMonthly Sales Report for 2022:\n\n");
	printf("Month      Sales\n");
    for (int i = 0; i < 12; i++) {
        printf("%-10s $%-20.2lf\n", monthNames[i], monthlySales[i]);
    }
	
	/* Calculatew the minumum and maximum sales */
    minSales = maxSales = monthlySales[0];
	const char *minMonth = monthNames[0];
    const char *maxMonth = monthNames[0];
    for (int i = 1; i < 12; i++) {
        if (monthlySales[i] < minSales) {
            minSales = monthlySales[i];
			minMonth = monthNames[i];
        }
        if (monthlySales[i] > maxSales) {
            maxSales = monthlySales[i];
			maxMonth = monthNames[i];
        }
    }

	/* Calculates the average salesi. */
    avgSales = calculateAverage(monthlySales, 12);

    /* Prints the sales summary report. */	
	printf("------------------------------------");
    printf("\nSales Summary Report:\n\n");
    printf("Minimum Sales: $%-10.2lf (%s)\n", minSales, minMonth);
    printf("Maximum Sales: $%-10.2lf (%s)\n", maxSales, maxMonth);
    printf("Average Sales: $%.2lf\n", avgSales);	
	
    /* Calculate six-month moving averages. */
    for (int i = 0; i < 12; i++) {
        double sum = 0.0;
        for (int j = i; j < i + 6 && j < 12; j++) {
            sum += monthlySales[j];
        }
        sixMonthMovingAverage[i] = sum / 6;
    }
	
	/* Print the six-month moving average report. */
	printf("------------------------------------");
    printf("\nSix-Month Moving Average Report:\n\n");
    for (int i = 0; i < 7; i++) {
        printf("%-10s - %s \t$%-10.2lf\n", monthNames[i], monthNames[i + 5], sixMonthMovingAverage[i]);
    }


	/* Creates an array that holds data for 12 months. */
	struct MonthlySalesData monthlyData[12];
	strcpy(monthlyData[0].monthName, "January");
	monthlyData[0].sales = 23458.01;
	strcpy(monthlyData[1].monthName, "Feburary");
	monthlyData[1].sales = 40112.00;
	strcpy(monthlyData[2].monthName, "March");
	monthlyData[2].sales = 56011.85;
	strcpy(monthlyData[3].monthName, "April");
	monthlyData[3].sales = 37820.88;
	strcpy(monthlyData[4].monthName, "May");
	monthlyData[4].sales = 37904.67;
	strcpy(monthlyData[5].monthName, "June");
	monthlyData[5].sales = 60200.22;
	strcpy(monthlyData[6].monthName, "July");
	monthlyData[6].sales = 72400.31;
	strcpy(monthlyData[7].monthName, "August");
	monthlyData[7].sales = 56210.89;
	strcpy(monthlyData[8].monthName, "September");
	monthlyData[8].sales = 67230.84;
	strcpy(monthlyData[9].monthName, "October");
	monthlyData[9].sales = 68233.12;
	strcpy(monthlyData[10].monthName, "November");
	monthlyData[10].sales = 80950.34;
	strcpy(monthlyData[11].monthName, "December");
	monthlyData[11].sales = 95225.22;

	sortSalesDataHighToLow(monthlyData, 12);

	/* Prints the sales reports from highest to lowest. */
	printf("------------------------------------\n");
    printf("Sales Report (Highest to Lowest):\n\n");
    printf("Month      Sales\n");
    for (int i = 0; i < 12; i++) {
        printf("%-10s $%.2lf\n", monthlyData[i].monthName, monthlyData[i].sales);	
    }	
	printf("------------------------------------\n");

	/* Closes the input file. */
    fclose(file);

    return 0;
}

