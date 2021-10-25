#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <macvdm.h>


#define EXIT_SUCCESS 0
#define EXIT_UNKNOWN_ERROR -1
#define EXIT_BAD_PORT_INDEX -2
#define EXIT_BAD_PARAMETERS -3

const char* command_dfu = "dfu";
const char* command_serial = "serial";
const char* command_reboot_serial = "reboot_serial";
const char* command_reboot = "reboot";

void PrintHelp(void) {
    uint8_t port_count = MacVDM_GetPortCount();
    printf("Port Count: %d\n\n", port_count);

    printf("Usage: %s <index> [<command>]\n", argv[0]);
    printf("Calling with only an index will tell you the status of the port\n\n");
    printf("Ports are zero indexed (the first port is port 0\n\n");
    printf("Commands:\n");
    printf("  serial - enter serial mode on both ends\n");
    printf("  reboot - reboot the target\n");
    printf("  reboot_serial - reboot the target and enter serial mode\n");
    printf("  dfu - put the target into DFU mode\n");
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        PrintHelp();

        return EXIT_SUCCESS;
    }

    if (argc == 2) {
        uint8_t port_index = atoi(argv[1]);
        macvdm_port_status_t port_status = MacVDM_GetPortStatus(port_index);

        switch (port_status)
        {
        case PORT_UNKNOWN:
            printf("Unknown port %d\n", port_index);
            return EXIT_BAD_PORT_INDEX;
        case PORT_DISCONNECTED:
            printf("Port %d: Disconnected\n", port_index);
            return EXIT_SUCCESS;
        case PORT_SINK:
            printf("Port %d: Sink\n", port_index);
            return EXIT_SUCCESS;
        case PORT_SOURCE:
            printf("Port %d: Source\n", port_index);
            return EXIT_SUCCESS;
        default:
            printf("Unknown result from port status\n");
            return EXIT_UNKNOWN_ERROR;
        }
    }

    if (argc < 3) {
        uint8_t port_index = atoi(argv[1]);
        char* command = argv[2];
        macvdm_result_t result;

        if (!strcmp(command, command_dfu)) {
            result = MacVDM_IssueDFUCommand(port_index);
        } else if (!strcmp(command, command_reboot)) {
            result = MacVDM_IssueRebootCommand(port_index);
        } else if (!strcmp(command, command_reboot_serial)) {
            result = MacVDM_IssueSerialCommand(port_index, true);
        } else if (!strcmp(command, command_serial)) {
            result = MacVDM_IssueSerialCommand(port_index, false);
        } else {
            printf("Unknown command\n");
            return EXIT_BAD_PARAMETERS;
        }

        if (result == SUCCESS) {
            printf("Success on port %d\n", port_index);
            return EXIT_SUCCESS;
        }

        printf("Error on port %d (error %d)\n", port_index, result);
        return result;
    }

    PrintHelp();
    return EXIT_BAD_PARAMETERS;
}
