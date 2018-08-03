#include "serialportdialog.h"
#include "ui_serialportdialog.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_LENGTH (1024)

static char ** find_devices(void)
{
    char **device = NULL;
    size_t size=0;
    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir("/sys/class/tty");

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return NULL;
    }

    while ((de = readdir(dr)) != NULL)
    {
            printf("%s\n", de->d_name);
            char check_driver[MAX_LENGTH];
            if (strlen(check_driver)<MAX_LENGTH - strlen("/device/driver"))//m=10 including 0 c=8
            {

                if( access( check_driver, F_OK ) != -1 )
                {
                    // file exists
                    char *entry  = strdup(de->d_name);
                    if (entry)
                    {
                        size++;
                        char **d = (char**)realloc(device,size*sizeof(char*));
                        if (d)
                        {

                        }
                    }
                }
            }
            else
                return NULL;
            free(check_driver);

    }
    closedir(dr);
    return 0;
}
SerialPortDialog::SerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortDialog)
{
    ui->setupUi(this);
    char **device_list = find_devices();
    //ui->portComboBox

    free(device_list);
}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

void SerialPortDialog::on_pushButton_clicked()
{
    this->~SerialPortDialog();
}