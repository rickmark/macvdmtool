
#ifndef _MACVDM_H
#define _MACVDM_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    kVDMPortUnknown,
    kVDMPortDisconnected,
    kVDMPortSource,
    kVDMPortSink
} macvdm_port_status_t;

typedef enum {
    kVDMSuccess = 0,
    kVDMFailureUnknown = 1
} macvdm_result_t;

uint8_t MacVDM_GetPortCount(void);
macvdm_port_status_t MacVDM_GetPortStatus(uint8_t index);
macvdm_result_t MacVDM_IssueRebootCommand(uint8_t index);
macvdm_result_t MacVDM_IssueDFUCommand(uint8_t index);
macvdm_result_t MacVDM_IssueSerialCommand(uint8_t index, bool reboot);

#ifdef __cplusplus
}
#endif

#endif