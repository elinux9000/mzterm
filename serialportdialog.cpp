#include "serialportdialog.h"
#include "ui_serialportdialog.h"
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string_list.h>
#define MAX_LENGTH (1024)

static str_list_t *find_devices(void)
{
    char **device = nullptr;
    size_t size=0;
    struct dirent *de;  // Pointer for directory entry
    str_list_t *list = create_list();

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir("/sys/class/tty");

    if (dr == nullptr)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return nullptr;
    }

    while ((de = readdir(dr)) != nullptr)
    {
            printf("%s\n", de->d_name);
            char check_driver[MAX_LENGTH];
            if (strlen(check_driver) + strlen("/device/driver") < MAX_LENGTH )//m=10 including 0 c=8
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
    }
    closedir(dr);
    return list;
}
SerialPortDialog::SerialPortDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialPortDialog)
{
    ui->setupUi(this);
    str_list_t *device_list = find_devices();
    device_list->destroy(device_list);

}

SerialPortDialog::~SerialPortDialog()
{
    delete ui;
}

void SerialPortDialog::on_pushButton_clicked()
{
    this->~SerialPortDialog();
}
