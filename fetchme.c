/*
 * Programa simple de recuperación de información do sistema
 * Autor: Miguel Blanco Godón [meluchoMZ@github]
 * Este software é libre e vén sen ningunha garantía
 */

/* 
 * Simple system info fetching program
 * Author: Miguel Blanco Godón [meluchoMZ@github]
 * This software is free and it comes with no warranty
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void fetch(void);
void get_os(void);
void get_kernel(void);
void get_uptime(void);
void get_CPU_info(void);
void get_mem_info(void);

int main(void)
{
	fetch();
	return 0;
}


void fetch(void)
{
	char * col0 =  "                     .\n"; 
	char * col1 =  "                    / V\\ \n";
	char * col2 =  "                  / `  /\n";
	char * col3 =  "                 <<   |\n";
	char * col4 =  "                 /    |\n";
	char * col5 =  "               /      | ";
	char * col6 =  "             /        | ";
	char * col7 =  "           /    \\  \\ /  ";
	char * col8 =  "          (      ) | |  ";
	char * col9 =  "  ________|   _/_  | |  ";
	char * col10 = "/__________\\______)\\__)\n";

	printf("%s", col0);
	printf("%s", col1);
	printf("%s", col2);
	printf("%s", col3);
	printf("%s", col4);
	printf("%s\t OS: ", col5); get_os();
	printf("%s\t Kernel: ", col6); get_kernel();
	printf("%s\t Up: ", col7); get_uptime();
	printf("%s\t CPU: ", col8); get_CPU_info();
	printf("%s\t Memory: ", col9); get_mem_info();
	printf("%s\n", col10);
}

void get_os(void)
{
	// A información do SO está separada en varios ficheiros
	// Neste caso, o "nome bonito" está no ficheiro /etc/os-release
	// Os information is separated in various files
	// In this case, the "pretty name" is in /etc/os-release
	FILE * f;
	char buffer[512];
	char key[64];
	char value[512];
	if ((f = fopen("/etc/os-release","r")) == NULL) {
		printf("unaccesible info! :-(\n");
	}

	while (fgets(buffer, 512, f) != NULL) {
		sscanf(buffer, "%[^=]=\"%[^\"]", key, value);
		if (strcmp(key, "PRETTY_NAME") == 0) {
			fclose(f);
			printf("%s\n", value);
			return;
		}
	}
	fclose(f);

	printf("unaccesible info! :-(\n");
}

void get_kernel(void)
{
	// A información da versión do kernel está no ficheiro /proc/version
	// Kernel version information is in /proc/version file
	FILE * f;
	char buffer[2048];
	char value[1024];
	if ((f = fopen("/proc/version","r")) == NULL) {
		printf("unaccesible info! :-(\n");
	}

	if (fgets(buffer, 2048, f) == NULL) {
		printf("unaccesible info! :-(\n");
	}
	sscanf(buffer, "%[^(]", value);

	printf("%s\n", value);
	fclose(f);
}

void get_uptime(void)
{
	// A información de tempo acendido está gardada no ficheiro 
	// /proc/uptime. Garda o tempo en segundos
	// Uptime information is stored in file /proc/uptime
	// It stores the time in seconds 
	FILE * fup;
	char  buffer[64];
	double uptime = 0;
	char  upt[64];

	if ((fup = fopen("/proc/uptime","r")) == NULL) {
		printf("unaccesible info! :-(\n");
	}

	if (fgets(buffer, 64, fup) == NULL) {
		printf("unaccesible info! :-(\n");
	}

	sscanf(buffer, "%lf", &uptime);

	fclose(fup);

	// convirtindo o tempo a minutos
	// converting uptime to minutes
	uptime = round(uptime / 60);
	snprintf(upt, 64, "%d", (int) uptime);
	printf("%s min\n", upt);
}

void get_CPU_info(void)
{
	// A información do procesador está en /proc/cpuinfo
	// CPU information is stored in /proc/cpuinfo
	FILE * f;
	char buffer[1024];
	char key[128];
	char value[1024];

	if ((f = fopen("/proc/cpuinfo","r")) == NULL) {
		printf("unaccesible info! :-(\n");
	}

	while (fgets(buffer, 1024, f) != NULL) {
		sscanf(buffer, "%[^:]:%[^\n]", key, value);
		if (strncmp(key, "model name", 10) == 0) {
			fclose(f);
			printf("%s\n", value);
			return;
		}
	}
	fclose(f);
	printf("unaccesible info! :-(\n");
}

void get_mem_info(void)
{
	// A información da memoria está no ficheiro /proc/meminfo
	// Memory information is in /proc/meminfo
	FILE * f;
	char buffer[128];
	char key[64];
	int total=0, available;
	char mem_ratio[64];

	if ((f = fopen("/proc/meminfo","r")) == NULL) {
		printf("unaccesible info! :-(\n");
	}

	while (fgets(buffer, 128, f) != NULL) {
		sscanf(buffer, "%[^:]:%d", key, &total);
		if (strcmp(key, "MemTotal") == 0) {
			break;
		}
	}
	fclose(f);
	if (total == 0) {
		printf("unaccesible info! :-(\n");
	}
	if ((f = fopen("/proc/meminfo","r")) == NULL) {
		printf("unaccesible info! :-(\n");
	}

	while (fgets(buffer, 128, f) != NULL) {
		sscanf(buffer, "%[^:]:%d", key, &available);
		if (strcmp(key, "MemAvailable") == 0) {
			break;
		}
	}
	fclose(f);

	// Convirtindo de kB a MB
	total = total / 1000;
	available = available / 1000;

	snprintf(mem_ratio, 64,  "%d MB / %d MB", total - available, total);
	printf("%s\n", mem_ratio);
}
