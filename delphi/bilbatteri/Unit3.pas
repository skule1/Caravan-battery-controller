unit Unit3;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants,
  System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, VrControls, VrButtons,
  VrLeds, VrAngularMeter, VrLabel, Vcl.ExtCtrls, Vcl.ComCtrls, IdBaseComponent,
  SyncObjs,
  IdComponent, IdTCPConnection, IdTCPClient, VrBlinkLed, VrCheckLed, VrSlider,
  VrGauge, VrSwitch, VrDesign, VCLTee.TeCanvas, VCLTee.TeeEdiGrad, frxCtrls;

const
  WM_UPDATE_PROGRESS = WM_APP + 101;

const
  WM_count = WM_APP + 102;

type

  TFixedCriticalSection = class(TCriticalSection)
  private
    FDummy: array [0 .. 95] of Byte;
  end;

  twifi = class(tthread) // leser comport
  protected
    procedure Execute; override;
  public
    linje: string;
    b:boolean;
    loggfil: textfile;
    // constructor create;
  end;

  TForm3 = class(TForm)
    IdTCPClient1: TIdTCPClient;
    Timer2: TTimer;
    Panel1: TPanel;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    Label4: TLabel;
    Edit2: TEdit;
    Button2: TButton;
    Button1: TButton;
    Memo1: TMemo;
    Button3: TButton;
    ListBox1: TListBox;
    Button4: TButton;
    TabSheet2: TTabSheet;
 //   VrAngularMeter3: TVrAngularMeter;
    VrLabel1: TVrLabel;
    VrLabel2: TVrLabel;
    VrLabel3: TVrLabel;
    VrLabel4: TVrLabel;
    VrAngularMeter2: TVrAngularMeter;
    VrAngularMeter6: TVrAngularMeter;
    Label33: TLabel;
    VrAngularMeter5: TVrAngularMeter;
    VrAngularMeter7: TVrAngularMeter;
    VrAngularMeter8: TVrAngularMeter;
    VrAngularMeter10: TVrAngularMeter;
    VrLed3: TVrLed;
    VrLed2: TVrLed;
    VrLed1: TVrLed;
    VrAngularMeter1: TVrAngularMeter;
    VrAngularMeter4: TVrAngularMeter;
    VrDemoButton2: TVrDemoButton;
    VrDemoButton3: TVrDemoButton;
    VrDemoButton4: TVrDemoButton;
    VrDemoButton5: TVrDemoButton;
    TabSheet3: TTabSheet;
    Panel2: TPanel;
    VrAngularMeter9: TVrAngularMeter;
    VrAngularMeter11: TVrAngularMeter;
    VrAngularMeter12: TVrAngularMeter;
    VrAngularMeter13: TVrAngularMeter;
    VrAngularMeter14: TVrAngularMeter;
    VrAngularMeter15: TVrAngularMeter;
    VrAngularMeter16: TVrAngularMeter;
    VrLed4: TVrLed;
    VrAngularMeter17: TVrAngularMeter;
    VrAngularMeter18: TVrAngularMeter;
    VrLed5: TVrLed;
    VrLed6: TVrLed;
    VrLabel9: TVrLabel;
    VrAngularMeter19: TVrAngularMeter;
    VrGauge1: TVrGauge;
    VrLabel10: TVrLabel;
    VrLabel13: TVrLabel;
    VrLabel6: TVrLabel;
    VrLabel11: TVrLabel;
    VrLabel14: TVrLabel;
    VrDemoButton1: TVrDemoButton;
    VrDemoButton6: TVrDemoButton;
    VrDemoButton7: TVrDemoButton;
    VrDemoButton8: TVrDemoButton;
    VrDemoButton9: TVrDemoButton;
    VrSlider1: TVrSlider;
    frxComboBox1: TfrxComboBox;
    TabSheet4: TTabSheet;
    Label2: TLabel;
    Label3: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label29: TLabel;
    Label30: TLabel;
    Label31: TLabel;
    Label32: TLabel;
    Edit1: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    Edit7: TEdit;
    Edit8: TEdit;
    Edit9: TEdit;
    Edit10: TEdit;
    Edit11: TEdit;
    Edit12: TEdit;
    Edit13: TEdit;
    VrLabel8: TVrLabel;
    VrLabel5: TVrLabel;
    Label1: TLabel;
    Label15: TLabel;
    Label26: TLabel;
    Button6: TButton;
    Button7: TButton;
    ScrollBar1: TScrollBar;
    Label27: TLabel;
    Button8: TButton;
    Button9: TButton;
    CheckBox1: TCheckBox;
    Timer1: TTimer;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    // procedure IdTCPClient1Connected(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure VrDemoButton7Click(Sender: TObject);
    procedure VrDemoButton8Click(Sender: TObject);
    procedure VrDemoButton9Click(Sender: TObject);
    procedure VrDemoButton6Click(Sender: TObject);
    procedure VrDemoButton1Click(Sender: TObject);
    procedure DoTerminate(Sender: TObject);
    procedure IdTCPClient1AfterBind(Sender: TObject);
    procedure IdTCPClient1BeforeBind(Sender: TObject);
    procedure IdTCPClient1Connected(Sender: TObject);
    procedure IdTCPClient1Disconnected(Sender: TObject);
    procedure IdTCPClient1SocketAllocated(Sender: TObject);
    procedure IdTCPClient1Status(ASender: TObject; const AStatus: TIdStatus;
      const AStatusText: string);
    procedure IdTCPClient1Work(ASender: TObject; AWorkMode: TWorkMode;
      AWorkCount: Int64);
    procedure IdTCPClient1WorkBegin(ASender: TObject; AWorkMode: TWorkMode;
      AWorkCountMax: Int64);
    procedure IdTCPClient1WorkEnd(ASender: TObject; AWorkMode: TWorkMode);
    procedure Button3Click(Sender: TObject);
    procedure frxComboBox1Change(Sender: TObject);
    procedure Edit1Exit(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Edit3Exit(Sender: TObject);
    procedure Edit5Exit(Sender: TObject);
    procedure Edit6Exit(Sender: TObject);
    procedure Edit11Exit(Sender: TObject);
    procedure Edit12Exit(Sender: TObject);
    procedure Edit4Exit(Sender: TObject);
    procedure Edit7Exit(Sender: TObject);
    procedure Edit8Exit(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure VrSlider1Changed(Sender: TObject);
    procedure Edit9Change(Sender: TObject);
    procedure Edit13Exit(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure ScrollBar1Change(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);

  private
    kk, nr: integer;
    st, st1: string;
    kontakt: boolean;
    stoplogfile, shift, alarm_batt1, alarm_batt2, alarm_gass: boolean;
    mld_turtall, mld_spenning, mld_strom, mld_temp, mld_brensel: string[60];
    RF_linje: string;
    i_max, u_max, u_min: real;
    Fsection: TCriticalSection;
    wifi: twifi;
    wifi_linje, kommando: string;
    LU, U1, U2, I1, I2, T1, T2, KT: real;
    b:boolean;
    procedure WMUpdateProgress(var Message: TMessage);
      message WM_UPDATE_PROGRESS;
    procedure WMcount(var Message: TMessage); message WM_count;

  public
    procedure UpdateProgress(Alinje: string);

  end;

var
  Form3: TForm3;

implementation

{$R *.dfm}

procedure TForm3.Button1Click(Sender: TObject);
var
  st, st1: string;
begin
  if (Button1.Caption = 'Connect') then
  begin
    wifi.Resume;
  Timer2.Enabled := true;
    Button1.Caption := 'Avbryt';
    Button2.Enabled := true;
    kontakt := true;
    Button4.Enabled := true;
    Button4.Caption := 'Suspend';
   // VrLed6.Color := clGreen;
   // VrLed5.Color := clGreen;
  end
  else
  begin
    wifi.Suspend;
    Button1.Caption := 'Connect';
    Button4.Enabled := false;
    Button4.Caption := 'Resume';
    // button2.Enabled:=false;
  //  VrLed5.Color := clBlack;
   // VrLed6.Color := clBlack;
    kontakt := false;
  end;
end;

procedure TForm3.Button2Click(Sender: TObject);
begin
  // if (not idtcpclient1.connected) then
  // idtcpclient1.connect();
  // IdTCPClient1.Socket.WriteLn('2:'+Edit2.Text);
end;

procedure TForm3.Button3Click(Sender: TObject);
begin
  IdTCPClient1.Connect;
  IdTCPClient1.ConnectTimeout := 30;
  IdTCPClient1.IOHandler.WriteLn('test');
  IdTCPClient1.Disconnect;
end;

procedure TForm3.Button4Click(Sender: TObject);
var
  b: boolean;
begin
  b := wifi.Terminated;
  if (Button4.Caption = 'Resume') then
  begin

    wifi.Resume;
    Button4.Caption := 'Suspend';
  end
  else
  begin
    Button4.Caption := 'Resume';
    wifi.Suspend;

  end;

end;

procedure TForm3.Button5Click(Sender: TObject);
begin
  VrAngularMeter18.Show;
end;

procedure TForm3.Button6Click(Sender: TObject);
begin
  if (not IdTCPClient1.Connected) then
  begin
    IdTCPClient1.Connect;

  end;
end;

procedure TForm3.Button7Click(Sender: TObject);
begin
  if IdTCPClient1.Connected then
  begin
    IdTCPClient1.IOHandler.InputBuffer.clear;
    IdTCPClient1.Disconnect;
  end;
end;

procedure TForm3.Button8Click(Sender: TObject);
begin
  if IdTCPClient1.Connected then
    IdTCPClient1.Socket.Write('bat1 on');
end;

procedure TForm3.Button9Click(Sender: TObject);
begin
  if IdTCPClient1.Connected then
    IdTCPClient1.Socket.Write('bat1 off');
end;

procedure TForm3.CheckBox1Click(Sender: TObject);
begin
  if CheckBox1.Checked then
    Timer2.Enabled := true
  else
    Timer2.Enabled := false;
end;

procedure TForm3.FormActivate(Sender: TObject);
begin
  kk := 0;
  kontakt := false;
  i_max := 50;
  u_min := 10;
  u_max := 15;
  wifi := twifi.Create;
  wifi.Suspend;
  nr := 0;
end;

procedure TForm3.FormCreate(Sender: TObject);
begin
  Fsection := TFixedCriticalSection.Create;
end;

procedure TForm3.frxComboBox1Change(Sender: TObject);
begin

  if (frxComboBox1.ItemIndex = 0) then
  begin
    VrSlider1.Visible := false;
    VrGauge1.Visible := true;
    kommando:='fan on';
  end
  else if (frxComboBox1.ItemIndex = 1) then
  begin
    VrSlider1.Visible := true;
    VrGauge1.Visible := true;
    IdTCPClient1.Socket.WriteLn('fan change' + #8 +
      inttostr(VrSlider1.Position));
   kommando:= 'fan change'+#8+inttostr(VrSlider1.Position);
  end
  else
  begin
    VrSlider1.Visible := false;
    VrGauge1.Visible := false;
  kommando:='fan off';

  end;

end;

procedure TForm3.IdTCPClient1AfterBind(Sender: TObject);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.IdTCPClient1BeforeBind(Sender: TObject);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.IdTCPClient1Connected(Sender: TObject);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.IdTCPClient1Disconnected(Sender: TObject);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.IdTCPClient1SocketAllocated(Sender: TObject);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.IdTCPClient1Status(ASender: TObject; const AStatus: TIdStatus;
  const AStatusText: string);
var
  i: integer;
  b: boolean;
begin
  // b:= IdTCPClient1.Connected;
  // i:=4;

end;

procedure TForm3.IdTCPClient1Work(ASender: TObject; AWorkMode: TWorkMode;
  AWorkCount: Int64);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.IdTCPClient1WorkBegin(ASender: TObject; AWorkMode: TWorkMode;
  AWorkCountMax: Int64);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.IdTCPClient1WorkEnd(ASender: TObject; AWorkMode: TWorkMode);
var
  i: integer;
begin
  i := 4;
end;

procedure TForm3.ScrollBar1Change(Sender: TObject);
begin
  Timer2.Interval := ScrollBar1.Position;
  Label27.Caption := inttostr(ScrollBar1.Position);
end;

procedure TForm3.DoTerminate(Sender: TObject);
begin
  // wifi.Terminate;
  // trad := NIL;
end;

procedure TForm3.Edit11Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit11.Text = '- Oppgi riktig verdi') then
    exit;
  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (KT > 0) then
  begin
    j := round(128 * strtofloat(Edit11.Text) / KT);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '8' + #9 + inttostr(j));
    Label24.Caption := 'kalib' + #9 + '8' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit12Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit12.Text = '- Oppgi riktig verdi') then
    exit;

  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (U1 > 0) then
  begin
    j := round(128 * strtofloat(Edit12.Text) / U1);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '9' + #9 + inttostr(j));
    Label29.Caption := 'kalib' + #9 + '1' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit13Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit13.Text = '- Oppgi riktig verdi') then
    exit;

  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (U1 > 0) then
  begin
    j := round(128 * strtofloat(Edit13.Text) / U1);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '10' + #9 + inttostr(j));
    Label30.Caption := 'kalib' + #9 + '1' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit1Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit1.Text = '- Oppgi riktig verdi') then
    exit;

  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (U1 > 0) then
  begin
    j := round(128 * strtofloat(Edit1.Text) / U1);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '1' + #9 + inttostr(j));
    Label13.Caption := 'kalib' + #9 + '1' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit3Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit3.Text = '- Oppgi riktig verdi') then
    exit;
  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (U2 > 0) then
  begin
    j := round(128 * strtofloat(Edit3.Text) / U2);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '2' + #9 + inttostr(j));
    Label16.Caption := 'kalib' + #9 + '2' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit4Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit4.Text = '- Oppgi riktig verdi') then
    exit;
  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (LU > 0) then
  begin
    j := round(128 * strtofloat(Edit4.Text) / LU);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '7' + #9 + inttostr(j));
    Label17.Caption := 'kalib' + #9 + '7' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit5Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit5.Text = '- Oppgi riktig verdi') then
    exit;
  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (I1 > 0) then
  begin
    j := round(128 * strtofloat(Edit5.Text) / I1);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '5' + #9 + inttostr(j));
    Label18.Caption := 'kalib' + #9 + '5' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit6Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit6.Text = '- Oppgi riktig verdi') then
    exit;
  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (I2 > 0) then
  begin
    j := round(128 * strtofloat(Edit6.Text) / I2);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '6' + #9 + inttostr(j));
    Label19.Caption := 'kalib' + #9 + '6' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit7Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit7.Text = '- Oppgi riktig verdi') then
    exit;
  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (T1 > 0) then
  begin
    j := round(128 * strtofloat(Edit7.Text) / T1);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '3' + #9 + inttostr(j));
    Label20.Caption := 'kalib' + #9 + '3' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit8Exit(Sender: TObject);
var
  j: integer;
begin
  if (Edit8.Text = '- Oppgi riktig verdi') then
    exit;
  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect();
  if (T2 > 0) then
  begin
    j := round(128 * strtofloat(Edit8.Text) / T2);
    IdTCPClient1.Socket.WriteLn('kalib' + #9 + '4' + #9 + inttostr(j));
    Label21.Caption := 'kalib' + #9 + '4' + #9 + inttostr(j);
  end;

end;

procedure TForm3.Edit9Change(Sender: TObject);
begin

end;

(*
  procedure TForm3.IdTCPClient1Connected(Sender: TObject);

  begin
  if idtcpclient1.Connected then
  if not idtcpclient1.IOHandler.InputBufferIsEmpty then
  try
  st:=    idtcpclient1.IOHandler.ReadLn   ;
  //   listbox2.AddItem(st,nil);
  memo1.Lines.Add(st);
  finally
  ;
  end;
  //   listbox2.AddItem( IdTCPClient1.Socket.ReadLn,nil);


  end;
*)
procedure TForm3.Timer1Timer(Sender: TObject);

begin
if alarm_batt1 then
      if b then
                  VrLed5.Transparent:=false
             else
                       VrLed5.Transparent:=true;

        b:=not b;

end;

procedure TForm3.Timer2Timer(Sender: TObject);
var
  b: boolean;
  l, linje: string;
begin

  if (wifi.Suspended and (Button4.Caption = 'Resume')) then
    exit;

  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect;
  wifi.Resume;
  exit;

  if (not IdTCPClient1.Connected) then
    IdTCPClient1.Connect;
  // idTcpClient1.Socket.WriteLn('test');
  IdTCPClient1.Socket.WriteLn('stop');
  IdTCPClient1.IOHandler.InputBuffer.clear;
  IdTCPClient1.Disconnect;
  wifi.Resume;

end;

procedure TForm3.VrDemoButton1Click(Sender: TObject);
var
  l,nothing: boolean;
begin

  if (VrDemoButton1.Caption = 'Koble til') then
  begin
   kommando:= 'bat1 on';
    VrDemoButton1.Caption := 'Koble fra';
  end
  else
  begin
    kommando:= 'bat1 off';
    VrDemoButton1.Caption := 'Koble til';
  end;
  if ((VrDemoButton1.Caption = 'Koble til') and
    (VrDemoButton6.Caption = 'Koble til')) then
    VrDemoButton8.Caption := 'Koble til';
  if ((VrDemoButton1.Caption = 'Koble fra') and
    (VrDemoButton6.Caption = 'Koble fra')) then
    VrDemoButton8.Caption := 'Koble fra';
 end;

procedure TForm3.VrDemoButton6Click(Sender: TObject);
begin

  if (VrDemoButton6.Caption = 'Koble til') then
  begin
    kommando:='bat2 on';
    VrDemoButton6.Caption := 'Koble fra';
  end
  else
  begin
    kommando:='bat2 off';
    VrDemoButton6.Caption := 'Koble til';
  end;
  if ((VrDemoButton1.Caption = 'Koble til') and
    (VrDemoButton6.Caption = 'Koble til')) then
    VrDemoButton8.Caption := 'Koble til';
  if ((VrDemoButton1.Caption = 'Koble fra') and
    (VrDemoButton6.Caption = 'Koble fra')) then
    VrDemoButton8.Caption := 'Koble fra';
end;

procedure TForm3.VrDemoButton9Click(Sender: TObject);
var
  st, st1: string;
begin

 Button1Click(Sender);
  if (VrDemoButton9.Caption = 'Avbryt nett') then
  begin

    kommando:='bat off';
    VrDemoButton9.Caption := 'Koble til nett';
    VrDemoButton8.Enabled := false;
    VrAngularMeter13.Position := 0;
  end
  else
  begin
    kommando:='bat on';
    VrDemoButton9.Caption := 'Avbryt nett';
    VrDemoButton8.Enabled := true;
    VrAngularMeter13.Position := 0;
  end;
end;

procedure TForm3.VrSlider1Changed(Sender: TObject);
begin
  IdTCPClient1.Connect;
  IdTCPClient1.Socket.WriteLn('fan change ' + #8 +
    inttostr(VrSlider1.Position));
  IdTCPClient1.Socket.WriteLn('stop');
  IdTCPClient1.IOHandler.InputBuffer.clear;
  IdTCPClient1.Disconnect;
  wifi.Resume;
end;

procedure TForm3.VrDemoButton8Click(Sender: TObject);
begin
  if (VrDemoButton8.Caption = 'Frakoble batt')  then
  begin
    VrDemoButton8.Caption := 'Koble til batt';
  kommando:= 'bat off';
    VrDemoButton1.Caption:='Koble til';
    VrDemoButton6.Caption:='Koble til';
   end
  else
  begin
    VrDemoButton8.Caption := 'Frakoble batt';
  kommando:= 'bat on';
     VrDemoButton1.Caption:='Koble fra';
    VrDemoButton6.Caption:='Koble fra';
  end;

 // VrDemoButton1Click(Sender);
  sleep(1000);


end;

procedure TForm3.VrDemoButton7Click(Sender: TObject);
begin
  alarm_batt1 := false;
  alarm_batt2 := false;
  kommando:='resett_alarm';
  VrDemoButton7.Enabled := false;


end;

procedure twifi.Execute;

begin
  assignfile(loggfil, 'e:\loggfil.log');
  rewrite(loggfil);
  with Form3 do
  begin
    kommando := '';
    while (true) do
    begin
     b:=false;
      while (IdTCPClient1.Connected) do
      begin
        b:=true;
        linje := IdTCPClient1.Socket.ReadLn;
        if kommando>'' then
        begin
         IdTCPClient1.Socket.WriteLn(kommando);
         kommando:='';
        end;
      if (linje = 'Slutt') then
       if IdTCPClient1.connected then
        begin
      IdTCPClient1.IOHandler.InputBuffer.clear;
      IdTCPClient1.Disconnect;
        end;
        if (linje > '') then
        begin
          writeln(loggfil, linje);
          UpdateProgress(linje);
        end;
      end;
      if IdTCPClient1.connected then
        begin
      IdTCPClient1.IOHandler.InputBuffer.clear;
      IdTCPClient1.Disconnect;
        end;
      b:=false;
      Suspend;
    end;
  end;

end;

procedure TForm3.UpdateProgress(Alinje: string);
begin
  Fsection.Enter();
  wifi_linje := Alinje;
  Fsection.Leave();
  PostMessage(Handle, WM_UPDATE_PROGRESS, 0, 0);
  PostMessage(Handle, WM_count, 0, 0);
  wifi.Suspend;
end;


procedure TForm3.WMcount(var Message: TMessage);
begin
  Fsection.Enter;
  Label26.Caption := inttostr(nr);
  inc(nr);
  Label26.update;
  Fsection.Leave;
end;

procedure TForm3.WMUpdateProgress(var Message: TMessage);
var
  AProgress, i, j, k: integer;
  Sender: TObject;
  linje, st, st1, st2, st3: String;

begin

  Fsection.Enter;
  // linje:=wifi_linje;
  (*
    if (linje='Slutt') then
    begin
    //Button4Click(Sender);
    // timer2.Enabled:=false;
    //idtcpclient1.Disconnect;
    FSection.Leave;
    wifi.Suspend;
    end;
  *)
  // memo1.Lines.Add(linje)   ;

  // if (not kontakt) then     exit;

  (*
    wifi := twifi.Create;
    wifi.FreeOnTerminate := True;
    wifi.OnTerminate := DoTerminate;
    // wifi.Start;
    (*
  *)
  // if (not idtcpclient1.connected) then
  // idtcpclient1.connect();

  // while (idtcpclient1.connected) do
  begin
    // st:=idtcpclient1.IOHandler.ReadLn;
    st := wifi_linje;
    // sleep(10);
    st1 := st; // +' : '+inttostr(kk);
    // inc(kk)  ;
    // FSection.Enter();
    Memo1.Lines.Add(st);
    if (Memo1.Lines.Count = 25) then
      Memo1.Lines.Delete(0);

    // FSection.Leave();

    if (VrLed5.Color <> clBlack) then
      if (alarm_batt1 and shift) then
        VrLed5.Transparent := true
      else
        VrLed5.Transparent := false;
    if (VrLed6.Color <> clBlack) then
      if (alarm_batt2 and shift) then
        VrLed6.Transparent := true
      else
        VrLed6.Transparent := false;
    shift := not shift;


    // if (not kontakt) then     exit;

    // if (not idtcpclient1.connected) then
    // idtcpclient1.connect();

    // while (idtcpclient1.connected) do
    // if (True)  then
    // try
    // st:=idtcpclient1.IOHandler.ReadLn;
    st3 := '';
    st1 := st; // +' : '+inttostr(kk);
    // inc(kk)  ;
    // memo1.Lines.Add(st1);
    // listbox2.AddItem(st1,nil);

    i := ansipos(#9, st);
    st1 := copy(st, 1, i - 1);
    st2 := copy(st, i + 1, length(st) - i);
    j := ansipos(#9, st2);
    if (j > 0) then
    begin
      st3 := copy(st2, j + 1, length(st2) - j);
      st2 := copy(st2, 1, j - 1);
    end;
    i := ansipos('.', st2);
    if (i > 0) then
      st2[i] := ',';
    if (st1 = 'T1 ') then
    begin
      T1 := strtofloat(st2);

      VrAngularMeter18.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      k := round(VrAngularMeter18.Position);
      VrAngularMeter18.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
    end
    else if (copy(st1, 1, 2) = 'R1') then
    begin
     if (st2='0') then
     begin
          VrLed5.Color := clGreen   ;
          VrDemoButton1.Caption:='Koble fra';
     end
       else
       begin
           VrLed5.Color := clBlack;
          VrDemoButton1.Caption:='Koble til';
       end;
    end
      else if (copy(st1, 1, 2) = 'R2') then
    begin
     if (st2='0') then
     begin
          VrLed6.Color := clGreen   ;
          VrDemoButton6.Caption:='Koble fra';
     end
       else
       begin
           VrLed6.Color := clBlack;
          VrDemoButton6.Caption:='Koble til';
       end;
     end
    else if (copy(st1, 1, 2) = 'I1') then
    begin
      I1 := strtofloat(st2);
      VrAngularMeter14.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter14.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
      if (strtofloat(st2) > i_max) then
        alarm_batt1 := true;
    end
      else if (copy(st1, 1, 2) = 'I2') then
    begin
      I2 := strtofloat(st2);
      VrAngularMeter15.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter15.Caption := inttostr(round(strtofloat(st2)));
      if (strtofloat(st2) > i_max) then
        alarm_batt2 := true;
    end

    else if (copy(st1, 1, 7) = 'KabTemp') then
    begin
      KT := strtofloat(st2);
      VrAngularMeter19.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter19.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
      // if ((strtofloat(st2)>U_max) or (strtofloat(st2)<U_min)) then
      // alarm_batt1:=true;
    end
    else if (copy(st1, 1, 7) = 'fan_set') then
    begin
      VrGauge1.Position := round(strtofloat(st2));
      // if ((strtofloat(st2)>U_max) or (strtofloat(st2)<U_min)) then
      // alarm_batt1:=true;
    end
    else if (copy(st1, 1, 2) = 'U1') then
    begin
      U1 := strtofloat(st2);
      VrAngularMeter13.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter13.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
      if ((strtofloat(st2) > u_max) or (strtofloat(st2) < u_min)) then
      begin
         alarm_batt1:= true;
         VrDemoButton1.Caption:='Koble til';
      end;
    end
(*   else if (copy(st1, 1, 2) = 'U2') then
    begin
      U2 := strtofloat(st2);
      VrAngularMeter12.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter12.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
      if ((strtofloat(st2) > u_max) or (strtofloat(st2) < u_min)) then
        alarm_batt2 := true;
    end
 *)   else if (st1 = 'T2 ') then
    begin
      T2 := strtofloat(st2);
      VrAngularMeter17.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter17.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
    end
    else if (copy(st1, 1, 4) = 'Gass') then
    begin
      VrAngularMeter9.Position := round(strtofloat(st2));
      VrAngularMeter9.Caption := st2;
    end
    else if (copy(st1, 1, 2) = 'U2') then
    begin
      U2 := strtofloat(st2);
      VrAngularMeter12.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter12.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
      if ((strtofloat(st2) > u_max) or (strtofloat(st2) < u_min)) then
      begin
         alarm_batt2:= true;
         VrDemoButton6.Caption:='Koble til';
      end;
    end
   else if (copy(st1, 1, 7) = 'Alarm 1') then
    begin
 //     if (VrLed5.Color <> clBlack) then
        if ((st2 = '1') or  alarm_batt1) then
        begin
          alarm_batt1 := true;
          VrDemoButton7.Enabled := true;
          VrLed5.Color := clYellow;
        end
        else
    //    begin
 //         alarm_batt1 := false;
   //       VrLed5.Color := clGreen;
   //     end;
    end
    else if (copy(st1, 1, 7) = 'Alarm 2') then
    begin
      if (VrLed5.Color <> clBlack) then
        if (st2 = '1') then
        begin
          alarm_batt2 := true;
          VrDemoButton7.Enabled := true;
          VrLed6.Color := clYellow;
        end
        else
        begin
          alarm_batt2 := false;
  //        VrLed6.Color := clGreen;
        end;
    end
    else if (copy(st1, 1, 12) = 'LadeSpenning') then
    begin
      LU := strtofloat(st2);
      VrAngularMeter11.Position :=
        round(strtofloat(st2) * strtofloat(st3) / 128);
      VrAngularMeter11.Caption := floattostrf(strtofloat(st2) * strtofloat(st3)
        / 128, ffFixed, 4, 1);
    end
    else
    begin
      alarm_batt2 := false;
    end;

    VrAngularMeter16.Position := VrAngularMeter14.Position +
      VrAngularMeter15.Position;
    VrAngularMeter16.Caption := floattostrf(VrAngularMeter16.Position,
      ffGeneral, 6, 2);



    //
    // finally
    // IdTCPClient1.Disconnect;
    // button1.Caption:='Connect';
    // button2.Enabled:=false;

    // finally

  end;
  // panel2.Refresh;
  Fsection.Leave;
  wifi.Resume;
end;

end.
