#include <iostream>
#include <string.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <typeinfo>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <direct.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <sqlite3.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//YYYY-MM-DD

using namespace std;
int op, op2;
bool t = true;

int main(int argc, char** argv) {
	sqlite3 *conn;
	sqlite3_stmt *res;
	int error=0;
	int rec_count=0;
	int actual, c, n;
	const char *tail;
	stringstream ss;
	string empno, name, job, mgr, hiredate, sal, comm, deptno, dn, dnm, loc, str, tm;
	string base="oracle-sample.db";
	//
	while(true){
		cout<<"Ingrese una opcion: "<<endl;
		cout<<"1) Listar..."<<endl;
		cout<<"2) Agregar..."<<endl;
		cout<<"3) Eliminar empleado"<<endl;
		cout<<"4) Listar jefe y empleado"<<endl;
		cout<<"5) Actualizar salario de empleados"<<endl;
		cout<<"6) Empleados de un departamento"<<endl;
		cout<<"7) Salir"<<endl;
		cin>>op;
		system("cls");
		switch(op){
			case 1://listar...
				while(t){
					cout<<"Ingrese una opcion: "<<endl;
					cout<<"1) Listar empleados"<<endl;
					cout<<"2) Listar departamentos"<<endl;
					cout<<"3) <-- Regresar"<<endl;
					cin>>op2;
					system("cls");
					switch(op2){
						case 1://list empleados
							error=sqlite3_open(base.c_str(),&conn);
							error=sqlite3_prepare_v2(conn, "select * from emp", 1000, &res, &tail);
							cout<<"Lista de empleados: "<<endl<<endl;
							while(sqlite3_step(res) == SQLITE_ROW){
								cout<<"Departamento No. "<<sqlite3_column_text(res,0)<<endl<<"Nombre: "<<sqlite3_column_text(res,1)<<endl<<"Ocupacion: "<<sqlite3_column_text(res,2)<<endl<<"Jefe: "<<sqlite3_column_text(res,3)<<endl<<"Fecha de Contratacion: "<<sqlite3_column_text(res,4)<<endl<<"Salario: "<<sqlite3_column_text(res,5)<<endl<<"Comision: "<<sqlite3_column_text(res,6)<<endl<<"Departamento No. "<<sqlite3_column_text(res,7)<<endl<<endl;
							}
							if(error!= SQLITE_OK){
								system("cls");
								cout<<"[!] Error al listar departamentos [!]"<<endl;
								system("pause");
							}
							sqlite3_close(conn);
							system("pause");
							system("cls");
							break;
						case 2://list depto.
							error=sqlite3_open(base.c_str(),&conn);
							error=sqlite3_prepare_v2(conn, "select * from dept", 1000, &res, &tail);
							cout<<"Lista de departamentos: "<<endl<<endl;
							while(sqlite3_step(res) == SQLITE_ROW){
								cout<<"Departamento No. "<<sqlite3_column_text(res,0)<<endl<<"Nombre del Departamento: "<<sqlite3_column_text(res,1)<<endl<<"Localizacion: "<<sqlite3_column_text(res,2)<<endl<<endl;
							}
							if(error!= SQLITE_OK){
								system("cls");
								cout<<"[!] Error al listar departamentos [!]"<<endl;
							}
							sqlite3_close(conn);
							system("pause");
							system("cls");
							break;
						case 3://regresar
							t=false;
							system("cls");
							break;
						default://error
							cout<<"[!] Opcion no valida [!]"<<endl;
							system("pause");
							system("cls");
						break;
					}
				}
				t=true;
				break;
			case 2://agregar...
				while(t){
					cout<<"Ingrese una opcion: "<<endl;
					cout<<"1) Agregar empleado"<<endl;
					cout<<"2) Agregar departamento"<<endl;
					cout<<"3) <-- Regresar"<<endl;
					cin>>op2;
					system("cls");
					switch(op2){
						case 1://add empleado
							cout<<"Numero de empleado: "<<endl;
							cin>>empno;
							cout<<"Nombre: "<<endl;
							cin>>name;
							cout<<"Ocupacion: "<<endl;
							cin>>job;
							cout<<"Numero de jefe: "<<endl;
							cin>>mgr;
							cout<<"Fecha de ingreso (YYYY-MM-DD): "<<endl;
							cin>>hiredate;
							cout<<"Salario: "<<endl;
							cin>>sal;
							cout<<"Comision: "<<endl;
							cin>>comm;
							cout<<"Numero de departamento: "<<endl;
							cin>>deptno;
							error=sqlite3_open(base.c_str(),&conn);
							str="insert into emp values('"+empno+"','"+name+"','"+job+"','"+mgr+"','"+hiredate+"','"+sal+"','"+comm+"','"+deptno+"')";
							error=sqlite3_exec(conn, str.c_str(), 0, 0, 0);
							if (error!= SQLITE_OK){
								system("cls");
								cout<<"[!] Error al agregar empleado [!]"<<endl;
							}else{
								system("cls");
								cout<<"Empleado agregado con exito!"<<endl;
							}
							sqlite3_close(conn);
							system("pause");
							system("cls");
							break;
						case 2://add depto.
							cout<<"Numero de departamento: "<<endl;
							cin>>dn;
							cout<<"Nombre de departamento: "<<endl;
							cin>>dnm;
							cout<<"Localizacion: "<<endl;
							cin>>loc;
							error=sqlite3_open(base.c_str(),&conn);
							str="insert into dept values('"+dn+"','"+dnm+"','"+loc+"')";
							error=sqlite3_exec(conn, str.c_str(), 0, 0, 0);
							if(error!= SQLITE_OK){
								system("cls");
								cout<<"[!] Error al agregar el departamento [!]"<<endl;
							}else{
								system("cls");
								cout<<"Departamento agregado con exito!"<<endl;
							}
							sqlite3_close(conn);
							system("pause");
							system("cls");
							break;
						case 3://regresar
							t=false;
							system("cls");
							break;
						default://error
							cout<<"[!] Opcion no valida [!]"<<endl;
							system("pause");
							system("cls");
						break;
					}
				}
				t=true;
				break;
			case 3://NOTA 2
					error=sqlite3_open(base.c_str(),&conn);
					error=sqlite3_prepare_v2(conn, "select * from emp", 1000, &res, &tail);
					cout<<"Ingrese el numero del empleado a eliminar: "<<endl;
					cin>>empno;
					str="delete from emp where empno= '"+empno+"'";
					error=sqlite3_exec(conn, str.c_str(),0,0,0);
					if(error!= SQLITE_OK){
						system("cls");
						cout<<"[!] Error al eliminar empleado [!]"<<endl;
					}else{
						system("cls");
						cout<<"Empleado eliminado con exito!"<<endl;
					}
					system("pause");
					system("cls");
					sqlite3_close(conn);
				break;
			case 4://liste su jefe, y todos los empleados trabajando bajo el mismo jefe.
				error=sqlite3_open(base.c_str(),&conn);
				error=sqlite3_prepare_v2(conn, "select emp.empno, emp.ename from emp", 1000, &res, &tail);
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<<"Numero de empleado: "<<sqlite3_column_text(res,0)<<" | Nombre: "<<sqlite3_column_text(res,1)<<endl;
				}
				cout<<"\nNumero del jefe del empleado: "<<endl;
				cin>>empno;
				str="select * from emp where empno='"+empno+"'";
				error=sqlite3_prepare_v2(conn, str.c_str(), 1000, &res, &tail);
				cout<<"\nJefe: "<<endl<<endl;
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<<"Departamento No. "<<sqlite3_column_text(res,0)<<endl<<"Nombre: "<<sqlite3_column_text(res,1)<<endl<<"Ocupacion: "<<sqlite3_column_text(res,2)<<endl<<"Jefe: "<<sqlite3_column_text(res,3)<<endl<<"Fecha de Contratacion: "<<sqlite3_column_text(res,4)<<endl<<"Salario: "<<sqlite3_column_text(res,5)<<endl<<"Comision: "<<sqlite3_column_text(res,6)<<endl<<"Departamento No. "<<sqlite3_column_text(res,7)<<endl<<endl;				}
				cout<<endl;
				str="select * from emp where mgr='"+empno+"'";
				error=sqlite3_prepare_v2(conn, str.c_str(), 1000, &res, &tail);
				cout<<"Empleados bajo el cargo de este jefe: "<<endl<<endl;
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<<"Departamento No. "<<sqlite3_column_text(res,0)<<endl<<"Nombre: "<<sqlite3_column_text(res,1)<<endl<<"Ocupacion: "<<sqlite3_column_text(res,2)<<endl<<"Jefe: "<<sqlite3_column_text(res,3)<<endl<<"Fecha de Contratacion: "<<sqlite3_column_text(res,4)<<endl<<"Salario: "<<sqlite3_column_text(res,5)<<endl<<"Comision: "<<sqlite3_column_text(res,6)<<endl<<"Departamento No. "<<sqlite3_column_text(res,7)<<endl<<endl;
				}
				cout<<endl;
				if (error!= SQLITE_OK){
					system("cls");
					cout<<"[!] Error al listar empleados [!]"<<endl;
				}
				system("pause");
				system("cls");
				sqlite3_close(conn);
				break;
			case 5://actualizar el salario
				c=0; n=0;
				error=sqlite3_open(base.c_str(),&conn);
				error=sqlite3_prepare_v2(conn, "select emp.empno,emp.ename from emp",1000,&res,&tail);
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<<sqlite3_column_text(res,0)<<", "<<sqlite3_column_text(res,1)<<endl;
				}
				cout<<endl;
				cout<<"Numero del empleado: "<<endl;
				cin>>empno;
				system("cls");
				str="select emp.sal from emp where empno='"+empno+"'";
				error=sqlite3_prepare_v2(conn, str.c_str(),1000,&res,&tail);
				while(sqlite3_step(res) == SQLITE_ROW){
					actual=atoi(reinterpret_cast<const char *>(sqlite3_column_text(res,0)));
					cout<<"Salario actual del empleado: "<<actual<<endl;
				}
				str="select emp.sal from emp where mgr='"+empno+"'";
				error=sqlite3_prepare_v2(conn, str.c_str(),1000,&res,&tail);
				while(sqlite3_step(res) == SQLITE_ROW){
					n=n+atoi(reinterpret_cast<const char *>(sqlite3_column_text(res,0)));
					c++;
				}
				if (c==0){
					n=actual;
				}else{
					n=(n/c)*2;
				}
				ss<<n;
				tm=ss.str();
				cout<<"Salario actualizado: "<<tm<<endl;
				str="update emp set sal='"+tm+"' where empno='"+empno+"'";
				error=sqlite3_exec(conn, str.c_str(),0,0,0);
				if (error!= SQLITE_OK){
					system("cls");
					cout<<"[!] Error al listar empleados [!]"<<endl;
				}
				cout<<"Salario actualizado con exito!"<<endl;
				system("pause");
				system("cls");
				sqlite3_close(conn);
				break;
			case 6://dado el numero, imprimir el nombre de ese departamento y listar todos los empleados
				error=sqlite3_open(base.c_str(),&conn);
				error=sqlite3_prepare_v2(conn, "select dept.deptno,dept.dname from dept", 1000, &res, &tail);
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<<"Numero de departamento: "<<sqlite3_column_text(res,0)<<" | Nombre: "<<sqlite3_column_text(res,1)<<endl;
				}
				cout<<endl;
				cout<<"Numero del departamento a listar: "<<endl;
				cin>>deptno;
				str="select * from dept where deptno='"+deptno+"'";
				error=sqlite3_prepare_v2(conn, str.c_str(), 1000, &res, &tail);
				cout<<"Departamento seleccionado: ";
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<<sqlite3_column_text(res,1)<<endl;
				}
				cout<<endl;
				str="select * from emp where deptno='"+deptno+"'";
				error=sqlite3_prepare_v2(conn, str.c_str(),1000,&res,&tail);
				cout<<"Empleados laborando en ese departamento: "<<endl;
				while(sqlite3_step(res) == SQLITE_ROW){
					cout<<setw(10)<<"Empno: "<<sqlite3_column_text(res,0)<<endl<<setw(10)<<"Ename: "<<sqlite3_column_text(res,1)<<endl<<setw(10)<<"Job: "<<sqlite3_column_text(res,2)<<endl<<setw(10)<<"Mgr: "<<sqlite3_column_text(res,3)<<endl<<setw(10)<<"Hiredate: "<<sqlite3_column_text(res,4)<<endl<<setw(10)<<"Sal: "<<sqlite3_column_text(res,5)<<endl<<setw(10)<<"Comm: "<<sqlite3_column_text(res,6)<<endl<<setw(10)<<"Deptno: "<<sqlite3_column_text(res,7)<<endl<<endl;
				}
				if (error!= SQLITE_OK){
					system("cls");
					cout<<"[!] Error al listar empleados [!]"<<endl;
				}
				sqlite3_close(conn);
				system("pause");
				system("cls");
				break;
			case 7://salir
				system("pause");
				return 1;
				break;
			default://error
				cout<<"[!] Opcion no valida [!]"<<endl;
				system("pause");
				system("cls");
				break;
		}
	}
	//
	return 0;
}
