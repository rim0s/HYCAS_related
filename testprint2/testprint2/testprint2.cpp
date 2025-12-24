


#include "pch.h"
#include <iostream>
#include <fstream>
#include "string"  
#include "vector"  
#include <objbase.h>
#include <locale.h>
#include <winuser.h>

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF") 
using namespace std;



int main()
{
	/*小票关键变量*/
	string shopname;	//门店名
	string flowno;		//流水号
	string poscode;		//款台号
	string saletime;	//销售时间
	string receivercode;//收款员编码
	string goodsname;	//商品名
	string gdsincode;	//商品自编码
	string amount;		//商品数量
	string singleprice;	//单品价格
	string single_shouldpay;	//单品总价
	string totalprice;	//全单总价
	string minmoney;	//优惠金额
	string shouldpay;	//全单总价收（付）金额
	string actpay;		//全单实收
	string classnum;	//种类数
	string goodsnum;	//件数
	string paymodename;	//支付方式名称
	string paymodemoney;//当前支付方式支付金额
	string receivemoney;//当前支付方式实收金额
	string salemode;	//是否优惠
	string charge;		//找零累计
	int gdslistnum;		//小票商品序号
	int sentcount;

	
	string shopcode;	//门店编码
	string longsaletime;//完整销售时间
	string salemode_tmp;	//31 和 3 是优惠   1 是正常销售
	string tmp_singlepride;
	string lineprice;	//单品总价
	string single_shouldpay_tmp;	//单品总价
	string shouldpay_tmp;
	string minmoney_tmp;	//优惠金额
	string charge_tmp;		//找零累计
	string actpay_tmp;
	string paymodemoney_tmp;
	float fpaymodemoney_tmp;
	float fshouldpay_tmp;
	float fcharge_tmp;		//找零累计
	float factpay_tmp;
	bool bprinterOK;

	///////////////test print func ////////////////////////////
	WinExec("taskkill /im pos_device.exe", SW_HIDE);
	Sleep(1000);
	ofstream logout;
	logout.open("C:\\mdcas\\printlog.txt",ios::ate);
	sentcount = 0;

	CoInitialize(NULL); //初始化COM环境           
	_ConnectionPtr pMyConnect(__uuidof(Connection));//定义连接对象并实例化对象 
	_RecordsetPtr pRst(__uuidof(Recordset));//定义记录集对象并实例化对象    //流水表结果
	_RecordsetPtr pRst_goods(__uuidof(Recordset));//定义记录集对象并实例化对象    //商品表结果
	_RecordsetPtr pRst_shopname(__uuidof(Recordset));//定义记录集对象并实例化对象    //店名表结果
	_RecordsetPtr pRst_paymode(__uuidof(Recordset));//定义记录集对象并实例化对象    //支付方式表结果

	try
	{
		pMyConnect->Open("Provider=SQLOLEDB; Server=8.8.8.8;Database=BSDBAS; uid=sa; pwd=TellMeWhy;", "", "", adModeUnknown);
	}
	catch (_com_error &e)
	{
		std::cout << "Initiate failed!" << endl;
		std::cout << e.Description() << endl;
		std::cout << e.HelpFile() << endl;
		return 0;
	}
	std::cout << "Connect succeed!" << endl;

	//步骤3：对数据源中的数据库/表进行操作
	try
	{
		string sqlsentensA = "select * from bil_flowlist ";//原始
		string sqlsentensB = "where flowno =";
		long long get_input_key;
		string sqlsentens_flowlist;
		std::cout << "重打小票程序" << endl;
		std::cout << "请输入要重打的流水号" << endl;
		std::cout << "1       回车------------退出程序" << endl;
		std::cout << "2       回车------------全部打印" << endl;
		std::cout << "流水号    回车------------指定打印" << endl;
		cin >> get_input_key;
		std::cout << "您输入的是:" << get_input_key << endl;
		
		if (get_input_key == 1)
			return 0;
		else if (get_input_key ==2)
		{
			std::cout << "此功能已被开发者禁用，请联系微信 rim0xs 咨询详情" << endl;
		}
		else
		{
			flowno = to_string(get_input_key).substr(to_string(get_input_key).size()-13,13);
			sqlsentens_flowlist = sqlsentensA + sqlsentensB + "'"+ flowno +"'";
			cout << "sql sentens is " << sqlsentens_flowlist << endl;
		}
		
		

		//pRst = pMyConnect->Execute("select top 2 * from bil_flowlist", NULL, adCmdText);//执行SQL： select * from gendat          
		pRst = pMyConnect->Execute(sqlsentens_flowlist.c_str(), NULL, adCmdText);//执行SQL： select * from gendat          
		if (!pRst->BOF)
		{
			pRst->MoveFirst();
		}
		else
		{
			std::cout << "未查询到符合条件的流水" << endl;
			return 0;
		}
		vector<_bstr_t> column_name;

		/*存储表的所有列名，显示表的列名*/
		for (int i = 0; i < pRst->Fields->GetCount(); i++)
		{
			std::cout << pRst->Fields->GetItem(_variant_t((long)i))->Name << " ";
			column_name.push_back(pRst->Fields->GetItem(_variant_t((long)i))->Name);
		}
		std::cout << endl;

		/*对表进行遍历访问,显示表中每一行的内容*/

		while (!pRst->adoEOF)
		{
			vector<_bstr_t>::iterator iter = column_name.begin();
			int column_count = 1;
			for (iter; iter != column_name.end(); iter++)
			{
				if (pRst->GetCollect(*iter).vt != VT_NULL)
				{
					std::cout << (_bstr_t)pRst->GetCollect(*iter) << " ";
					if (column_count == 1)
						flowno = (_bstr_t)pRst->GetCollect(*iter); //第一列 流水号
					if (column_count == 2)
						actpay_tmp = (_bstr_t)pRst->GetCollect(*iter); //第二列  实收
					if (column_count == 5)
						longsaletime = (_bstr_t)pRst->GetCollect(*iter); //第五列  销售时间     需要进一步处理
					if (column_count == 7)
						receivercode = (_bstr_t)pRst->GetCollect(*iter); //第七列  收款员编码
					if (column_count == 9)
						poscode = (_bstr_t)pRst->GetCollect(*iter); //第九列  款台号
					if (column_count == 11)
					{
						shopcode = (_bstr_t)pRst->GetCollect(*iter); //第十一列  门店号
					//==========================================================================
						try
						{
							string sqlsentens = "select deptname from inf_department where deptcode = " + shopcode;
							pRst_shopname = pMyConnect->Execute(sqlsentens.c_str(), NULL, adCmdText);//执行SQL： select * from gendat          
							if (!pRst_shopname->BOF)
							{
								pRst_shopname->MoveFirst();
								
							}
							else
							{
								std::cout << "Data is empty!" << endl;
								return 0;
							}
							vector<_bstr_t> column_name_department;

							/*存储表的所有列名，显示表的列名*/
							for (int i2 = 0; i2 < pRst_shopname->Fields->GetCount(); i2++)
							{
								//std::cout << pRst_shopname->Fields->GetItem(_variant_t((long)i))->Name << " ";
								column_name_department.push_back(pRst_shopname->Fields->GetItem(_variant_t((long)i2))->Name);
							}
							//std::cout << endl;

							/*对表进行遍历访问,显示表中每一行的内容*/
							while (!pRst_shopname->adoEOF)
							{
								vector<_bstr_t>::iterator iter2 = column_name_department.begin();
								for (iter2; iter2 != column_name_department.end(); iter2++)
								{
									if (pRst_shopname->GetCollect(*iter2).vt != VT_NULL)
									{
										//std::cout << (_bstr_t)pRst_shopname->GetCollect(*iter2) << " ";
										shopname = (_bstr_t)pRst_shopname->GetCollect(*iter2); //第十一列  门店号
									}
									else
									{
										//std::cout << "NULL" << endl;
									}
								}
								pRst_shopname->MoveNext();
								//std::cout << endl;
							}
						}
						catch (_com_error &e)
						{
							std::cout << e.Description() << endl;
							std::cout << e.HelpFile() << endl;
							return 0;
						}
						try
						{
							pRst_shopname->Close();     //关闭记录集                      
							pRst_shopname.Release();//释放记录集对象指针               
						}
						catch (_com_error &e)
						{
							std::cout << e.Description() << endl;
							std::cout << e.HelpFile() << endl;
							return 0;
						}
					}
						//===================================================================

				}
				else
				{
					//std::cout << "NULL" << endl;
					std::cout << "NULL ";
				}

				column_count += 1;
			}
			/////////////////////////
			int timeindex = longsaletime.size();
			timeindex -= 9;
			if (timeindex > 0) 
			{
				saletime = longsaletime.substr(longsaletime.size() - 9, 10);
			}
			///////////////////////////////票头开始//////////////////////////////////////
			if (remove("C:\\mdcas\\posprint.txt") == 0)
			{
				cout << "删除成功" << endl;

			}
			else
			{
				cout << "删除失败" << endl;
			}
			ofstream output;
			output.open("C:\\mdcas\\posprint.txt", std::ofstream::out);
			std::cout << endl;
			std::cout << "  欢迎光临" << shopname << endl;
			output << "  欢迎光临" << shopname << endl;
			std::cout << endl;
			output << endl;
			std::cout << "流水号:" << flowno << "" << saletime << endl;
			output << "流水号:" << flowno << "" << saletime << endl;
			std::cout << "收款机:" << poscode << "   收款员:" << receivercode << endl;
			output << "收款机:" << poscode << "  收款员:" << receivercode << endl;
			std::cout << "--------------------------------" << endl;
			output << "--------------------------------" << endl;
			///////////////////////////////票头结束//////////////////////////////////////

			//////////////////商品列表查询部分开始///////////////////////////////////////////////////////////
			try
			{
				string sqlsentens_goods = "select bil_goodsflow.flowno,bil_goodsflow.gdsincode,inf_goods.gdsname,bil_goodsflow.salemode,bil_goodsflow.amount,bil_goodsflow.shouldpay,bil_goodsflow.actualpay from bil_goodsflow, inf_goods where bil_goodsflow.gdsincode = inf_goods.gdsincode and bil_goodsflow.flowno = \'" + flowno + "\'";
				pRst_goods = pMyConnect->Execute(sqlsentens_goods.c_str(), NULL, adCmdText);//执行SQL： select * from gendat          
				if (!pRst_goods->BOF)
				{
					pRst_goods->MoveFirst();

				}
				else
				{
					std::cout << "异常:该流水下无商品信息" << endl;
					return 0;
				}
				vector<_bstr_t> column_name_goods;

				/*存储表的所有列名，显示表的列名*/
				for (int i3 = 0; i3 < pRst_goods->Fields->GetCount(); i3++)
				{
					//std::cout << pRst_goods->Fields->GetItem(_variant_t((long)i3))->Name << " ";//显示列名
					column_name_goods.push_back(pRst_goods->Fields->GetItem(_variant_t((long)i3))->Name);
				}
				//std::cout << endl;

				/*对表进行遍历访问,显示表中每一行的内容*/
				gdslistnum = 1;
				fshouldpay_tmp = 0.00;
				while (!pRst_goods->adoEOF)
				{
					vector<_bstr_t>::iterator iter3 = column_name_goods.begin();
					int column_count_goods = 1;
					for (iter3; iter3 != column_name_goods.end(); iter3++)
					{
						if (pRst_goods->GetCollect(*iter3).vt != VT_NULL)
						{
							if(column_count_goods == 2)
								gdsincode  = (_bstr_t)pRst_goods->GetCollect(*iter3); //第二列  商品编码
							if (column_count_goods == 3)
								goodsname = (_bstr_t)pRst_goods->GetCollect(*iter3); //第三列  商品名称
							if (column_count_goods == 4)
								salemode_tmp = (_bstr_t)pRst_goods->GetCollect(*iter3); //第四列  是否优惠
							if (column_count_goods == 5)
								amount = (_bstr_t)pRst_goods->GetCollect(*iter3); //第五列  数量
							if (column_count_goods == 6)
								shouldpay_tmp = (_bstr_t)pRst_goods->GetCollect(*iter3); //第六列  应付金额
							if (column_count_goods == 7)
								lineprice = (_bstr_t)pRst_goods->GetCollect(*iter3); //第七列  实付金额
						}
						else
						{
							//std::cout << "NULL" << endl;
						}
						column_count_goods += 1;
					}
					int bsalemode = salemode_tmp.find("3");
					if (bsalemode >= 0)
					{
						std::cout << to_string(gdslistnum) << "." << goodsname << "(优惠)" << endl;
						output << to_string(gdslistnum) << "." << goodsname << "(优惠)" << endl;
					}
					else
					{
						std::cout << to_string(gdslistnum) << "." << goodsname << endl;
						output << to_string(gdslistnum) << "." << goodsname << endl;
					}
					tmp_singlepride = to_string(atof(lineprice.c_str()) / atof(amount.c_str()));
					singleprice = tmp_singlepride.substr(0, tmp_singlepride.find(".") + 3);
					single_shouldpay_tmp = to_string(atof(lineprice.c_str()));
					single_shouldpay = single_shouldpay_tmp.substr(0, single_shouldpay_tmp.find(".") + 3);

					std::cout << gdsincode << " " << amount << " * " << singleprice << "  \t"<< single_shouldpay << endl;
					output << gdsincode << " " << amount << " * " << singleprice << "  \t" << single_shouldpay << endl;
					fshouldpay_tmp += atof(shouldpay_tmp.c_str());
					pRst_goods->MoveNext();
					gdslistnum += 1;

				}

				shouldpay_tmp = to_string(fshouldpay_tmp);
				shouldpay = shouldpay_tmp.substr(0, shouldpay_tmp.find(".") + 3);
			}
			catch (_com_error &e)
			{
				std::cout << e.Description() << endl;
				std::cout << e.HelpFile() << endl;
				return 0;
			}
			try
			{
				pRst_goods->Close();     //关闭记录集                        
				pRst_goods.Release();//释放记录集对象指针               
			}
			catch (_com_error &e)
			{
				std::cout << e.Description() << endl;
				std::cout << e.HelpFile() << endl;
				return 0;
			}
			std::cout << "--------------------------------" << endl;
			output << "--------------------------------" << endl;
			//////////////////商品列表查询部分结束///////////////////////////////////////////////////////////

			//////////////////小计部分开始///////////////////////////////////////////////////////////
			std::cout << "总计: " << shouldpay << endl;
			output << "总计: " << shouldpay << endl;
			if (atof(shouldpay.c_str()) - atof(actpay_tmp.c_str()) > 0)
			{
				minmoney_tmp = to_string(atof(shouldpay.c_str()) - atof(actpay_tmp.c_str()));
				minmoney = minmoney_tmp.substr(0, minmoney_tmp.find(".") + 3);
				factpay_tmp = atof(actpay_tmp.c_str());
				actpay_tmp = to_string(factpay_tmp);
				actpay = actpay_tmp.substr(0, actpay_tmp.find(".") + 3);
				std::cout << "优惠: "<< minmoney << endl;
				output << "优惠: " << minmoney << endl;
				std::cout << "应收: " << actpay << endl;
				output << "应收: " << actpay << endl;
			}
			else 
			{
			}
			std::cout << "--------------------------------" << endl;
			output << "--------------------------------" << endl;
			
			
			//////////////////小计部分结束///////////////////////////////////////////////////////////



			//////////////////支付部分开始///////////////////////////////////////////////////////////
			try
			{
				fcharge_tmp = 0.0;
				string sqlsentens_paymode = "select bil_moneyflow.flowno,inf_frontpaymode.paymodename,bil_moneyflow.payamount,bil_moneyflow.no,bil_moneyflow.receivemoney from bil_moneyflow,inf_frontpaymode where bil_moneyflow.paymode=inf_frontpaymode.paymode and bil_moneyflow.flowno = \'" + flowno + "\'";
				pRst_paymode = pMyConnect->Execute(sqlsentens_paymode.c_str(), NULL, adCmdText);//执行SQL： select * from gendat          
				if (!pRst_paymode->BOF)
				{
					pRst_paymode->MoveFirst();

				}
				else
				{
					std::cout << "异常:该流水下无支付信息!" << endl;
					return 0;
				}
				vector<_bstr_t> column_name_paymode;

				/*存储表的所有列名，显示表的列名*/
				for (int i4 = 0; i4 < pRst_paymode->Fields->GetCount(); i4++)
				{
					//std::cout << pRst_paymode->Fields->GetItem(_variant_t((long)i4))->Name << " ";//显示列名
					column_name_paymode.push_back(pRst_paymode->Fields->GetItem(_variant_t((long)i4))->Name);
				}
				//std::cout << endl;

				/*对表进行遍历访问,显示表中每一行的内容*/
				fshouldpay_tmp = 0.00;
				while (!pRst_paymode->adoEOF)
				{
					vector<_bstr_t>::iterator iter4 = column_name_paymode.begin();
					int column_count_paymode = 1;
					for (iter4; iter4 != column_name_paymode.end(); iter4++)
					{
						if (pRst_paymode->GetCollect(*iter4).vt != VT_NULL)
						{
							if (column_count_paymode == 2)
								paymodename = (_bstr_t)pRst_paymode->GetCollect(*iter4); //第二列  支付方式名称
							if (column_count_paymode == 3)
								paymodemoney = (_bstr_t)pRst_paymode->GetCollect(*iter4); //第三列  支付方式付款金额
							if (column_count_paymode == 5)
								receivemoney = (_bstr_t)pRst_paymode->GetCollect(*iter4); //第五列  支付方式收款金额
						}
						else
						{
							//std::cout << "NULL" << endl;
						}
						column_count_paymode += 1;
					}

					std::cout << paymodename << ": " << paymodemoney << endl;
					output << paymodename << ": " << paymodemoney << endl;
					fcharge_tmp += atof(paymodemoney.c_str()) - atof(receivemoney.c_str());
					pRst_paymode->MoveNext();
				}

				charge_tmp = to_string(fcharge_tmp);
				charge = charge_tmp.substr(0, charge_tmp.find(".") + 3);

			}
			catch (_com_error &e)
			{
				std::cout << e.Description() << endl;
				std::cout << e.HelpFile() << endl;
				return 0;
			}
			try
			{
				pRst_paymode->Close();     //关闭记录集                
				pRst_paymode.Release();//释放记录集对象指针               
			}
			catch (_com_error &e)
			{
				std::cout << e.Description() << endl;
				std::cout << e.HelpFile() << endl;
				return 0;
			}

			std::cout << endl;

			//////////////////支付部分结束///////////////////////////////////////////////////////////


			//////////////////票尾开始///////////////////////////////////////////////////////////
			
			std::cout << endl;
			output << endl;
			std::cout << endl;
			output << endl;
			std::cout << "            重打小票" << endl;
			output << "         重打小票" << endl;
			output.close();
			
			WinExec("c:\\mdcas\\pos_device.exe", SW_HIDE);
			::Sleep(3000);
			HWND hWnd2;
			hWnd2 = FindWindow((LPCTSTR)L"FNWND360", (LPCTSTR)L"pos_device");//得到目标窗口句柄
			if (hWnd2 == NULL)
			{
				std::cout << "没有找到目标程序" << endl;
				bprinterOK = FALSE;
			}
			else
			{
				bprinterOK = TRUE;
				::PostMessage(hWnd2, 1024 + 59, 0, 0);
				sentcount += 1;
			}
			Sleep(1000);
			TerminateProcess(hWnd2, 0);
			
			logout << flowno << endl;

			//////////////////票尾结束///////////////////////////////////////////////////////////


			pRst->MoveNext();
			std::cout << endl;
		}
	}
	catch (_com_error &e)
	{
		std::cout << e.Description() << endl;
		std::cout << e.HelpFile() << endl;
		return 0;
	}

	//步骤4：关闭数据源
	/*关闭数据库并释放指针*/
	try
	{
		pRst->Close();     //关闭记录集               
		pMyConnect->Close();//关闭数据库               
		pRst.Release();//释放记录集对象指针               
		pMyConnect.Release();//释放连接对象指针
		
	}
	catch (_com_error &e)
	{
		std::cout << e.Description() << endl;
		std::cout << e.HelpFile() << endl;
		return 0;
	}
	CoUninitialize(); //释放COM环境
	logout << "共" << sentcount << endl;
	logout.close();
	return 0;
	///////////////////////////////
}


