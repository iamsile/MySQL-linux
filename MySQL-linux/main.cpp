//
//  main.cpp
//  MySQL-linux
//
//  Created by taowei on 13-11-8.
//  Copyright (c) 2013年 taowei. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void create(MYSQL *conn_ptr) {
	int k;
	k = mysql_query(conn_ptr, "create table t1(ID INT,name CHAR(5),birthday DATE, primary key(ID)");

	if (k) {
		fprintf(stderr, "error: %s\n", mysql_error(conn_ptr));
	} else {
		printf("Create success!\n");
	}
}

void insert(MYSQL *conn_ptr) {
	int i, k = 0;
	for (i = 0; i < 1000000; i++) {
		k=1;
		mysql_query(conn_ptr, "insert into t1(ID,name,birthday),values(10000,'lv','1989-02-09')");
	}
	if (k) {
		fprintf(stderr, "error: %s\n", mysql_error(conn_ptr));
	} else {
		printf("Insert success!\n");
	}
}

void output(MYSQL *conn_ptr) {
	int k = 0;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row = NULL;
	MYSQL_FIELD *field;

	k = mysql_query(conn_ptr, "select * from t1");
	if (k) {
		fprintf(stderr, "error: %s\n", mysql_error(conn_ptr));
	} else {
		k = mysql_store_result(conn_ptr);
		if (k) {
			int colNum = mysql_num_fields(k);
			while (field = mysql_fetch_field(k)) {
				printf("field name: %s\n", field->name);
				printf("field org name:%s\n", field->org_name);
				//....

			}
		}
	}
}

int main(int argc, const char * argv[])
{
	MYSQL *conn_ptr;
	conn_ptr = mysql_init(NULL);
	if (!conn_ptr) {
		fprintf(stderr, "mysql_init failed\n");
		return EXIT_FAILURE;
	}
	conn_ptr = mysql_real_connect(conn_ptr, "localhost","root","root","test",0,NULL,0);
	if (!conn_ptr) {
		fprintf(stderr, "connection failed\n");
	}
	create(conn_ptr);
	insert(conn_ptr);
	output(conn_ptr);
	mysql_close(conn_ptr);
    return 0;
}

