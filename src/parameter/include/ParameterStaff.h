//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#ifndef _Staff_H_
#define _Staff_H_
struct MSG_STAFF
{
      char Network[2];
      char Plaza[2];
      char collno[6];
      char collname[20];
      char password[8];
      char identify;
      char Privilege[50];
      char Validate[10];
      char Status[10];
      char Capture;
      char Founder[6];
}//endstructStaff
#define  LENGHT_MSG_STAFF 116
void InitMsgStaff(void);
struct MSG_STAFF *GetMsgStaff(void);
void SetStaffMsgNetwork(char* InputNetwork);
void SetStaffMsgPlaza(char* InputPlaza);
void SetStaffMsgcollno(char* Inputcollno);
void SetStaffMsgcollname(char* Inputcollname);
void SetStaffMsgpassword(char* Inputpassword);
void SetStaffMsgidentify(char Inputidentify);
void SetStaffMsgPrivilege(char* InputPrivilege);
void SetStaffMsgValidate(char* InputValidate);
void SetStaffMsgStatus(int InputStatus);
void SetStaffMsgCapture(char InputCapture);
void SetStaffMsgFounder(char* InputFounder);
#endif //define t_tablename

