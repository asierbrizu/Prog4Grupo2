/*
 * BD.cpp
 *
 *  Created on: 3 jun. 2021
 *      Author: Asier
 */

#include "sqlite3.h"
#include "BD.h"
#include <stdio.h>
#include "string.h"
#include <iostream>

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

bool existeUsuario(sqlite3 *db, Jugador j) {
	const char *data = "Callback function called";
	char *zErrMsg = 0;

	sqlite3_stmt *stmt;

	string email = j.getEMail();

	string comando = "SELECT * FROM usuario WHERE email='" + email + "';";
	char sql[comando.length() + 1];
	strcpy(sql, comando.c_str());

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (INSERT)\n" << endl;
		cout << sqlite3_errmsg(db) << endl;

	}

	result = sqlite3_step(stmt);
	while (result == SQLITE_ROW) {

		return true;

	}

	return false;
}
int crearUsuario(sqlite3 *db, Jugador j) {
	const char *data = "Callback function called";
	char *zErrMsg = 0;

	sqlite3_stmt *stmt;

	string email = j.getEMail();
	string contraseya = j.getContrasenya();

	if (!existeUsuario(db, j)) {
		string comando = "INSERT INTO usuario (email, contraseya) VALUES ('"
				+ email + "', '" + contraseya + "')";

		char sql[comando.length() + 1];
		strcpy(sql, comando.c_str());

		int result = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
		if (result != SQLITE_OK) {
			cout << "Error preparing statement (INSERT)\n" << endl;
			cout << sqlite3_errmsg(db) << endl;
			return result;
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}

		string comando2 = "INSERT INTO estadistica VALUES ('" + email
				+ "', 0, 0)";

		char sql2[comando2.length() + 1];
		strcpy(sql2, comando2.c_str());

		result = sqlite3_exec(db, sql2, callback, (void*) data, &zErrMsg);
		if (result != SQLITE_OK) {
			cout << "Error preparing statement (INSERT)\n" << endl;
			cout << sqlite3_errmsg(db) << endl;
			return result;
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		return result;
	} else {
		cout << "El usuario introducido ya esta en la base de datos" << endl;
	}

	return 0;
}

bool confirmarUsuario(sqlite3 *db, Jugador j) {
	sqlite3_stmt *stmt;

	string email = j.getEMail();
	string contraseya = j.getContrasenya();

	string comando = "SELECT email, contraseya FROM usuario WHERE (email = '"
			+ email + "' AND contraseya = '" + contraseya + "')";

	char sql[comando.length() + 1];
	strcpy(sql, comando.c_str());

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (INSERT)\n" << endl;
		cout << sqlite3_errmsg(db) << endl;

	}

	result = sqlite3_step(stmt);
	while (result == SQLITE_ROW) {
		return true;

	}
	return false;
}

int mostrarEstadisticas(sqlite3 *db, Jugador j) {
	const char *data = "Callback function called";
	char *zErrMsg = 0;

	sqlite3_stmt *stmt;

	string email = j.getEMail();

	string comando =
			"SELECT partidasJugadas, partidasGanadas FROM estadistica WHERE email = '"
					+ email + "'";

	char sql[comando.length() + 1];
	strcpy(sql, comando.c_str());

	int result = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (INSERT)\n" << endl;
		cout << sqlite3_errmsg(db) << endl;
		return result;
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	return result;

}
int sumarVictoria(sqlite3 *db, Jugador j) {
	const char *data = "Callback function called";
	char *zErrMsg = 0;

	string email = j.getEMail();

	string comando =
			"UPDATE estadistica SET partidasGanadas = partidasGanadas + 1 WHERE email = '"
					+ email + "'";

	char sql[comando.length() + 1];
	strcpy(sql, comando.c_str());

	int result = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (INSERT)\n" << endl;
		cout << sqlite3_errmsg(db) << endl;
		return result;
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	return result;
}

int sumarPartida(sqlite3 *db, Jugador j) {
	const char *data = "Callback function called";
	char *zErrMsg = 0;

	string email = j.getEMail();

	string comando =
			"UPDATE estadistica SET partidasJugadas = partidasJugadas + 1 WHERE email = '"
					+ email + "'";

	char sql[comando.length() + 1];
	strcpy(sql, comando.c_str());

	int result = sqlite3_exec(db, sql, callback, (void*) data, &zErrMsg);
	if (result != SQLITE_OK) {
		cout << "Error preparing statement (INSERT)\n" << endl;
		cout << sqlite3_errmsg(db) << endl;
		return result;
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	return result;
}
