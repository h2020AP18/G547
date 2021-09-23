
#include "chardev.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */



 // Functions for the ioctl calls
 
u_int16_t buffer;

int ioctl_gyroscope_x_axis (int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc,IOCTL_GYROSCOPE_X_AXIS , message);

    if (ret_val == 0) {
        printf("ioctl_ failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_gyroscope_y_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_GYROSCOPE_Y_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_gyroscope_z_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc,IOCTL_GYROSCOPE_Z_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_accelerometer_x_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_ACCELEROMETER_X_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_accelerometer_y_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_ACCELEROMETER_Y_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_accelerometer_z_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_ACCELEROMETER_Z_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_magnetometer_x_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_MAGNETOMETER_X_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_magnetometer_y_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_MAGNETOMETER_Y_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_magnetometer_z_axis(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_MAGNETOMETER_Z_AXIS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}


int ioctl_barometer_pressure(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_BAROMETER_PRESSURE, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}


 // Main - Call the ioctl functions
 
int main()
{
    int count,select;
    int file_desc, ret_val;
    char *msg = "Message passed by ioctl\n";

    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) {
        printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }

    printf("Select the option to be displayed from the below options:   \n");
    
    printf("1. x-axis measure from Gyroscope  \n 2. Y-axis measure from Gyroscope  \n 3. Z -axis measure from gyroscope \n 4. x-axis measure from Accelorometer  \n 5. Y-axis measure from accelerometer  \n 6. Z -axis measure from accelerometer \n 7. x-axis measure from magnetometer  \n 8. Y-axis measure from magnetometer  \n 9. Z -axis measure from magnetometer \n 10. Pressure in pascals obtained from Barometer ");
    
     scanf("%d",&select);
     
     switch(select)
     {
          case 1: ioctl_gyroscope_x_axis(file_desc,"1");
                  break;
          case 2: ioctl_gyroscope_y_axis(file_desc,"2");
                  break;
          case 3: ioctl_gyroscope_z_axis(file_desc,"3");
                  break;
          case 4: ioctl_accelerometer_x_axis(file_desc,"4");
                  break;
          case 5: ioctl_accelerometer_y_axis(file_desc,"5");
                  break;
          case 6: ioctl_accelerometer_z_axis(file_desc,"6");
                  break;
          case 7: ioctl_magnetometer_x_axis(file_desc,"7");
                  break;
          case 8: ioctl_magnetometer_y_axis(file_desc,"8");
                  break;
          case 9: ioctl_magnetometer_z_axis(file_desc,"9");
                  break;
          case 10:ioctl_barometer_pressure(file_desc,"10");
                  break;
          default: printf(" INVALID");
                  break;
     }  
 
    count = read(file_desc, &buffer, sizeof(buffer));
    close(file_desc);
    return 0;
}

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
	





