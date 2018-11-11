#include <iostream>
#include <cstdlib>
#include <fstream>

#include <ncurses.h>

#include "globalDefine.h"
#include "inputHelper.h"

#include "windowManager.h"
#include "color.h"
#include "control.h"
#include "container.h"
#include "stackContainer.h"

#include "spacer.h"
#include "label.h"
#include "textBox.h"

#ifdef __DEBUG__
void testPrint(Control* ctrl)
{
	werase(stdscr);
	wrefresh(stdscr);
	for (int y = 0; y < (*ctrl).getSize().height; ++y)
	{
		move((*ctrl).getPosition().y + y, (*ctrl).getPosition().x);
		for (int x = 0; x < (*ctrl).getSize().width; ++x)
		{
			addch((*ctrl).getCharacterForPrinting(x, y));
		}
	}
	wrefresh(stdscr);
}
#endif

//Global Variables
HorizontalStackContainer settingsContainer;

int selectedCategory;
HorizontalStackContainer hotkeyBarContainer;

HorizontalStackContainer tunnelSettingsContainer;
HorizontalStackContainer connectionContainer;
HorizontalStackContainer pathContainer;

int selectedPath;
int pathCount;
VerticalStackContainer pathListContainer;
VerticalStackContainer pathSettingsContainer;
std::vector<Container*> pathSettingsVector;

void selectCategory(int id)
{
	if(selectedCategory == id) return;

	if(selectedCategory > -1)
	{
		(*hotkeyBarContainer.controls[(selectedCategory*3)]).setDefaultColor(Color_Window_Inactive_Normal);
	}

	selectedCategory = id;

	(*hotkeyBarContainer.controls[(selectedCategory*3)]).setDefaultColor(Color_Window_Active_Selected);

	if(settingsContainer.controls.size() > 0) settingsContainer.controls.pop_back();

	switch(selectedCategory)
	{
		case 0: settingsContainer.addControl(&tunnelSettingsContainer); break;
		case 1: settingsContainer.addControl(&connectionContainer); break;
		case 2: settingsContainer.addControl(&pathContainer); break;
		default: break;
	}
}

void selectPath(int id)
{
	if(selectedPath > -1) (*pathListContainer.controls[selectedPath]).setDefaultColor(Color_Window_Inactive_Normal);

	selectedPath = id;

	(*pathListContainer.controls[selectedPath]).setDefaultColor(Color_Window_Active_Normal);

	if(pathSettingsContainer.controls.size() > 0) pathSettingsContainer.controls.pop_back();
	pathSettingsContainer.addControl(pathSettingsVector[selectedPath]);
}

void selectPathPrev()
{
	if(selectedPath > 0) selectPath(selectedPath-1);
}

void selectPathNext()
{
	if((selectedPath + 1) < signed(pathSettingsVector.size())) selectPath(selectedPath+1);
}

void addPath()
{
	HorizontalStackContainer* tempSettingsContainer = new HorizontalStackContainer;
	(*tempSettingsContainer).addSizingParameter(SizingProperty(20, false));
	(*tempSettingsContainer).addSizingParameter(SizingProperty(-1, true));

		VerticalStackContainer* tempLabelsContainer = new VerticalStackContainer;
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempLabelsContainer).addSizingParameter(SizingProperty(1, false));

		(*tempLabelsContainer).addControl(new Label("Interface"));
		(*tempLabelsContainer).addControl(new Label("IP version"));
		(*tempLabelsContainer).addControl(new Label("Public IP address"));
		(*tempLabelsContainer).addControl(new Label("Private IP address"));
		(*tempLabelsContainer).addControl(new Label("Remote IP address"));
		(*tempLabelsContainer).addControl(new Label("Gateway IP address"));
		(*tempLabelsContainer).addControl(new Label("Keepalive time"));
		(*tempLabelsContainer).addControl(new Label("Dead time"));
		(*tempLabelsContainer).addControl(new Label("Weight out"));
		(*tempLabelsContainer).addControl(new Label("Weight in"));
		(*tempLabelsContainer).addControl(new Label("Cmd Default"));
		(*tempLabelsContainer).addControl(new Label("Status"));

		VerticalStackContainer* tempInputsContainer = new VerticalStackContainer;
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));
		(*tempInputsContainer).addSizingParameter(SizingProperty(1, false));

		(*tempInputsContainer).addControl(new TextBox(""));
		(*tempInputsContainer).addControl(new TextBox("4"));
		(*tempInputsContainer).addControl(new TextBox(""));
		(*tempInputsContainer).addControl(new TextBox(""));
		(*tempInputsContainer).addControl(new TextBox(""));
		(*tempInputsContainer).addControl(new TextBox(""));
		(*tempInputsContainer).addControl(new TextBox("0"));
		(*tempInputsContainer).addControl(new TextBox("0"));
		(*tempInputsContainer).addControl(new TextBox("1"));
		(*tempInputsContainer).addControl(new TextBox("1"));
		(*tempInputsContainer).addControl(new TextBox(""));
		(*tempInputsContainer).addControl(new TextBox("0"));

	(*tempSettingsContainer).addControl(tempLabelsContainer);
	(*tempSettingsContainer).addControl(tempInputsContainer);

	pathSettingsVector.push_back(tempSettingsContainer);

	pathListContainer.addSizingParameter(SizingProperty(1, false));
	pathListContainer.addControl(new Label("Path" + std::to_string(pathSettingsVector.size()-1)));

	selectPath(pathSettingsVector.size()-1);
}

void deletePath()
{
	if(pathSettingsVector.size() < 2) return;

}

void saveConfig()
{
	//interface.conf
	std::ofstream interface;
	interface.open("interface.conf", std::ofstream::trunc);

	interface << "####################### Interface Information: ###############################" << std::endl;
	interface << "# Here you can configure the tunnel interface, which is going to be handled  #" << std::endl;
	interface << "# by the MPT server. The general section contains the information            #" << std::endl;
	interface << "# necessary for the further interpretation. These are the following:         #" << std::endl;
	interface << "#                                                                            #" << std::endl;
	interface << "# accept_remote = [VALUE], where the VALUE determines the acceptance         #" << std::endl;
	interface << "# of a remote new connection request (0=don't accept; 1=accept)              #" << std::endl;
	interface << "#                                                                            #" << std::endl;
	interface << "# cmdport_local = [VALUE], where the VALUE determines the portnum            #" << std::endl;
	interface << "# we use to receive commands from a remote mptsrv or mpt client              #" << std::endl;
	interface << "#                                                                            #" << std::endl;
	interface << "# cmd_timeout = [VALUE], where the VALUE determines the timeout (seconds)    #" << std::endl;
	interface << "# for waiting the answer of the server when issuing an mpt command.          #" << std::endl;
	interface << "#                                                                            #" << std::endl;
	interface << "##############################################################################" << std::endl << std::endl;

	interface << "[general]" 		<< std::endl;
	interface << "tunnel_num = 1" 	<< std::endl;
	interface << "accept_remote = " << (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[0]).getText() << std::endl;
	interface << "cmdport_local = " << (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[1]).getText() << std::endl;
	interface << "cmd_timeout = " 	<< (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[2]).getText() << std::endl << std::endl;

	interface << "[tun_0]" 			<< std::endl;
	interface << "name = " 			<< (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[3]).getText() << std::endl;
	interface << "mtu = " 			<< (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[4]).getText() << std::endl;
	interface << "ipv4_addr = " 	<< (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[5]).getText() << std::endl;
	interface << "ipv6_addr = " 	<< (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[6]).getText() << std::endl;

	interface.close();

	//ipv4.conf
	std::ofstream ipv4;
	ipv4.open("ipv4.conf", std::ofstream::trunc);

	ipv4 << ";###################### Multipath Connection Information: ###############" << std::endl;
	ipv4 << "[connection]"			<< std::endl;
	ipv4 << "name = " 				<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[0]).getText() << std::endl;
	ipv4 << "permission = "			<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[1]).getText() << std::endl;
	ipv4 << "ip_ver = " 			<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[2]).getText() << std::endl;
	ipv4 << "ip_local = "  			<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[3]).getText() << std::endl;
	ipv4 << "local_port = " 		<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[4]).getText() << std::endl;
	ipv4 << "ip_remote = " 			<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[5]).getText() << std::endl;
	ipv4 << "remote_port = " 		<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[6]).getText() << std::endl;
	ipv4 << "remote_cmd_port = " 	<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[7]).getText() << std::endl;
	ipv4 << "path_count = " 		<< pathSettingsVector.size() << std::endl;
	ipv4 << "network_count = 0" 	<< std::endl;
	ipv4 << "status = " 			<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[8]).getText() << std::endl;
	ipv4 << "reorder_window = " 	<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[9]).getText() << std::endl;
	ipv4 << "max_buffdelay_msec = " << (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[10]).getText() << std::endl;
	ipv4 << "auth_type = " 			<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[11]).getText() << std::endl;
	ipv4 << "auth_key = "			<< (*(TextBox*)(*(Container*)connectionContainer.controls[1]).controls[12]).getText() << std::endl << std::endl;

	ipv4 << ";########################## PATHS ############################" << std::endl << std::endl;
	for(unsigned int i = 0; i < pathSettingsVector.size(); i++)
	{
		ipv4 << "[path_" << i << "]" 	<< std::endl;
		ipv4 << "interface_name = "		<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[0]).getText() << std::endl;
		ipv4 << "ip_ver = " 			<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[1]).getText() << std::endl;
		ipv4 << "public_ipaddr = " 		<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[2]).getText() << std::endl;
		if((*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[3]).getText().length() > 0)
		{
			ipv4 << "private_ipaddr = " 	<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[3]).getText() << std::endl;
		}
		ipv4 << "gw_ipaddr = " 			<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[5]).getText() << std::endl;
		ipv4 << "remote_ipaddr = " 		<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[4]).getText() << std::endl;
		ipv4 << "keepalive_time = " 	<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[6]).getText() << std::endl;
		ipv4 << "dead_time = " 			<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[7]).getText() << std::endl;
		ipv4 << "weight_out = " 		<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[8]).getText() << std::endl;
		ipv4 << "weight_in = " 			<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[9]).getText() << std::endl;
		ipv4 << "cmd_default = " 		<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[10]).getText() << std::endl;
		ipv4 << "status = " 			<< (*(TextBox*)(*(Container*)(*pathSettingsVector[i]).controls[1]).controls[11]).getText() << std::endl << std::endl;
	}

	ipv4 << ";####################### NETWORKS #####################################" << std::endl;

	ipv4.close();
}

int main()
{
#ifdef __DEBUG__
	//Delete debugLog.txt file's contents!
	_debugErase();
#endif

	//Init ncurses
	initscr();	//Init screen
	cbreak();	//Disable input buffering
	noecho();	//Disable input reflection
	keypad(stdscr, true);	//Enable special character capture
	curs_set(0);	//Hide the cursor

	if(has_colors() == false) //Check if terminal has color support
	{
		endwin();
		std::cout << "Your terminal does not support color!\n";
		std::exit(1);
	}
	start_color();
	setupColors();

	//Init
	selectedCategory = -1;
	selectedPath = -1;
	pathCount = 0;

	//Setup controls
	WindowManager wm(stdscr);

		VerticalStackContainer wmContainer;
		wmContainer.addSizingParameter(SizingProperty(-1, true));
		wmContainer.addSizingParameter(SizingProperty(1, false));
		wmContainer.setDefaultColor(Color_Window_Inactive_Normal);
		wmContainer.setDefaultFocusColor(Color_Window_Active_Normal);

			//HorizontalStackContainer settingsContainer;
			settingsContainer.addSizingParameter(SizingProperty(-1, true));

				//TunnelSettings
				//HorizontalStackContainer tunnelSettingsContainer;
				tunnelSettingsContainer.addSizingParameter(SizingProperty(20, false));
				tunnelSettingsContainer.addSizingParameter(SizingProperty(-1, true));

					VerticalStackContainer tunnelSettingsLabelsContainer;
					tunnelSettingsLabelsContainer.isSelectable = false;
					tunnelSettingsLabelsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsLabelsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsLabelsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsLabelsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsLabelsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsLabelsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsLabelsContainer.addSizingParameter(SizingProperty(1, false));

					tunnelSettingsLabelsContainer.addControl(new Label("Accept Remote"));
					tunnelSettingsLabelsContainer.addControl(new Label("Cmdport Local"));
					tunnelSettingsLabelsContainer.addControl(new Label("Cmd Timeout"));
					tunnelSettingsLabelsContainer.addControl(new Label("Name"));
					tunnelSettingsLabelsContainer.addControl(new Label("MTU"));
					tunnelSettingsLabelsContainer.addControl(new Label("IPv4 Address"));
					tunnelSettingsLabelsContainer.addControl(new Label("IPv6 Address"));

					VerticalStackContainer tunnelSettingsInputsContainer;
					tunnelSettingsInputsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsInputsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsInputsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsInputsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsInputsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsInputsContainer.addSizingParameter(SizingProperty(1, false));
					tunnelSettingsInputsContainer.addSizingParameter(SizingProperty(1, false));

					tunnelSettingsInputsContainer.addControl(new TextBox("1"));
					tunnelSettingsInputsContainer.addControl(new TextBox("60456"));
					tunnelSettingsInputsContainer.addControl(new TextBox("25"));
					tunnelSettingsInputsContainer.addControl(new TextBox("tun0"));
					tunnelSettingsInputsContainer.addControl(new TextBox("1464"));
					tunnelSettingsInputsContainer.addControl(new TextBox(""));
					tunnelSettingsInputsContainer.addControl(new TextBox(""));

				tunnelSettingsContainer.addControl(&tunnelSettingsLabelsContainer);
				tunnelSettingsContainer.addControl(&tunnelSettingsInputsContainer);

				//Connection Settings
				//HorizontalStackContainer connectionContainer;
				connectionContainer.addSizingParameter(SizingProperty(20, false));
				connectionContainer.addSizingParameter(SizingProperty(-1, true));

					VerticalStackContainer connectionLabelsContainer;
					connectionLabelsContainer.isSelectable = false;
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));
					connectionLabelsContainer.addSizingParameter(SizingProperty(1, false));

					connectionLabelsContainer.addControl(new Label("Name"));
					connectionLabelsContainer.addControl(new Label("Permission"));
					connectionLabelsContainer.addControl(new Label("IP version"));
					connectionLabelsContainer.addControl(new Label("Local IP address"));
					connectionLabelsContainer.addControl(new Label("Local port"));
					connectionLabelsContainer.addControl(new Label("Remote IP address"));
					connectionLabelsContainer.addControl(new Label("Remote port"));
					connectionLabelsContainer.addControl(new Label("Remote Cmd port"));
					connectionLabelsContainer.addControl(new Label("Status"));
					connectionLabelsContainer.addControl(new Label("Reorder window"));
					connectionLabelsContainer.addControl(new Label("Max buffdelay msec"));
					connectionLabelsContainer.addControl(new Label("Auth type"));
					connectionLabelsContainer.addControl(new Label("Auth key"));

					VerticalStackContainer connectionInputsContainer;
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));
					connectionInputsContainer.addSizingParameter(SizingProperty(1, false));

					connectionInputsContainer.addControl(new TextBox(""));
					connectionInputsContainer.addControl(new TextBox("3"));
					connectionInputsContainer.addControl(new TextBox("4"));
					connectionInputsContainer.addControl(new TextBox(""));
					connectionInputsContainer.addControl(new TextBox(""));
					connectionInputsContainer.addControl(new TextBox(""));
					connectionInputsContainer.addControl(new TextBox(""));
					connectionInputsContainer.addControl(new TextBox(""));
					connectionInputsContainer.addControl(new TextBox("0"));
					connectionInputsContainer.addControl(new TextBox("0"));
					connectionInputsContainer.addControl(new TextBox("200"));
					connectionInputsContainer.addControl(new TextBox("0"));
					connectionInputsContainer.addControl(new TextBox("0"));

				connectionContainer.addControl(&connectionLabelsContainer);
				connectionContainer.addControl(&connectionInputsContainer);

				//Path settings
				//HorizontalStackContainer pathContainer;
				pathContainer.addSizingParameter(SizingProperty(20, false));
				pathContainer.addSizingParameter(SizingProperty(-1, true));

					//VerticalStackContainer pathListContainer;
					pathListContainer.isSelectable = false;

					//VerticalStackContainer pathSettingsContainer;
					pathSettingsContainer.addSizingParameter(SizingProperty(-1, true));
				
				pathContainer.addControl(&pathListContainer);
				pathContainer.addControl(&pathSettingsContainer);

			//HorizontalStackContainer hotkeyBarContainer;
			hotkeyBarContainer.addSizingParameter(SizingProperty(9, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(13, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(8, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(-1, true));
			hotkeyBarContainer.addSizingParameter(SizingProperty(7, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(7, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(6, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(9, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(-1, true));
			hotkeyBarContainer.addSizingParameter(SizingProperty(7, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(1, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(2, false));
			hotkeyBarContainer.addSizingParameter(SizingProperty(8, false));

			hotkeyBarContainer.addControl(new Label("F1 Tunnel"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Label("F2 Connection"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Label("F3 Paths"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("F5 Prev"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Label("F6 Next"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Label("F7 Add"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Label("F8 Remove"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("F9 Save"));
			hotkeyBarContainer.addControl(new Spacer());
			hotkeyBarContainer.addControl(new Label("|"));
			hotkeyBarContainer.addControl(new Label("F10 Exit"));

		wmContainer.addControl(&settingsContainer);
		wmContainer.addControl(&hotkeyBarContainer);

	wm.setChild(&wmContainer);

	selectCategory(2);
	addPath();
	wm.input(KEY_RIGHT);
	selectCategory(0);
	wm.draw();

	//Main control loop
	int ch = 0;
	while((ch = getch()) != KEY_F(10))
	{
		switch(ch)
		{
			case KEY_F(1): selectCategory(0); wm.draw(); break;
			case KEY_F(2): selectCategory(1); wm.draw(); break;
			case KEY_F(3): selectCategory(2); wm.draw(); break;
			case KEY_F(5): if(selectedCategory != 2) break; selectPathPrev(); wm.draw(); break;
			case KEY_F(6): if(selectedCategory != 2) break; selectPathNext(); wm.draw(); break;
			case KEY_F(7): if(selectedCategory != 2) break; addPath(); wm.input(KEY_RIGHT); wm.draw(); break;
			case KEY_F(8): if(selectedCategory != 2) break; deletePath(); wm.draw(); break;
			case KEY_F(9): saveConfig(); break;
			//case KEY_F(5): wm.draw(); break;
			default: wm.input(ch); break;
		}
	}

	//Shutdown
	endwin();

#ifdef __DEBUG__
	//Debug info after shutdown
	std::cout << (*(TextBox*)(*(Container*)tunnelSettingsContainer.controls[1]).controls[5]).getText() << "\n";

	settingsContainer.print();
#endif

	std::exit(0);
}