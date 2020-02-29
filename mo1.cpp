#include<iostream>
#include<cmath>
using namespace std;

double func(double x) {
	return pow(x, 5) - pow(x, 3) + 2 * x + 2;
	//return pow(x, 2);
}

double derivFunc(double x) {
	return 5 * pow(x, 4) - 3 * pow(x, 2) + 2;
	//return 2 * x;
}

double doubleDerivFunc(double x) {
	return 20 * pow(x, 3) - 6 * x;
	//return 2;
}

bool isUnimodal(double a, double b, double eps) {
	for (double i = a; i < b; i += eps/10) {
		for (double j = i; j < b; j += eps/10) {
			if ((func(i) <= func(a)) && (func(j) <= func(b)) && (func(i) == func(j))) {
				return true;
			}
		}
	}
	return false;
}

double calcDivideInterval(double a, double b, double del, double eps, int& iter) {

	double totalIterations = 0;
	bool isCalced = false;
	double u1, u2, J1, J2;
	while (!isCalced) {
		while (b - a >= eps) {
			iter++;
			u1 = (b + a - del) / 2;
			u2 = (b + a + del) / 2;
			J1 = func(u1);
			J2 = func(u2);

			if (J1 < J2) {
				b = u2;
			}
			else if (J1 > J2) {
				a = u1;
			}
			else if (J1 == J2) {
				b = u2;
				a = u1;
			}
			//cout << "\nJ1 = " << J1 << " J2 = " << J2;
			if (iter > 999) {
				del /= 2;
				cout << "максимальное количество итераций превышено, del было уменьшено вдвое (оно равно " << del << ")\n";
				break;
			}
		}
		if (b - a < eps) {
			isCalced = true;
		}
		//cout << "количество итераций сейчас " << iter << '\n';
		totalIterations += iter;
		iter = 0;
	}
	iter = totalIterations;
	return (b + a) / 2;
}

double divideInterval(double a, double b, double del, double eps, int& iter) {

	int answer;

	cout << "\nМЕТОД ДЕЛЕНИЯ ОТРЕЗКА ПОПОЛАМ:\n";
	cout << "Изначально в методе используются следующие значения входных параметров:\na = " << a << ", b = " << b
		<< ", del = " << del << ", eps = " << eps << '\n';
	cout << "для их изменения введите 1, в противном случае введите 0\n";
	cin >> answer;
	if (answer == 1) {
		cout << "Введите значения a, b, del\n";
		cin >> a >> b >> del;
	}

	double answerDivideInterval = calcDivideInterval(a, b, del, eps, iter);
	cout << "\nрезультат работы метода (значение точки минимума): " << answerDivideInterval;
	cout << "\nколичество итераций: " << iter;
	return answerDivideInterval;
}

double calcGoldRatio(double a, double b, double eps, int& iter) {
	int n = 0;
	double alpha = (sqrt(5) - 1) / 2;
	double alpha1 = (3 - sqrt(5)) / 2;
	double u1, u2, J1, J2;
	double res, Jres;

	while (b - a >= eps) {
		iter++;
		u1 = a + alpha1 * (b - a);
		u2 = a + alpha * (b - a);
		J1 = func(u1);
		J2 = func(u2);
		if (J1 < J2) {
			b = u2;
			u2 = u1;
			J2 = J1;
			u1 = a + alpha1 * (b - a);
			J1 = func(u1);
		} else if (J1 > J2) {
			a = u1;
			u1 = u2;
			J1 = J2;
			u2 = a + alpha * (b - a);
			J2 = func(u2);
		}
		else {
			b = u2;
			a = u1;
			u1 = a + alpha1 * (b - a);
			u2 = a + alpha * (b - a);
			J1 = func(u1);
			J2 = func(u2);
		}
	}

	if (b - a < eps) {
		res = (b + a) / 2;
		Jres = func(res);
	}

	return res;
}

double goldRatio(double a, double b, double eps, int& iter) {
	
	int answer;

	cout << "\n\nМЕТОД ЗОЛОТОГО СЕЧЕНИЯ: ";
	cout << "\nИзначально в методе используются следующие значения входных параметров:\na = " << a << ", b = " << b
		<< ", eps = " << eps << '\n';
	cout << "для их изменения введите 1, в противном случае введите 0\n";
	cin >> answer;
	if (answer == 1) {
		cout << "Введите значения a, b\n";
		cin >> a >> b;
	}

	double answerGoldRatio = calcGoldRatio(a, b, eps, iter);
	cout << "\nрезультат работы метода (значение точки минимума): " << answerGoldRatio;
	cout << "\nколичество итераций: " << iter;
	return answerGoldRatio;

}

double calcParabola(double u1, double u3, double& del, double eps, int& iter, bool& isFound) {

	int sumIter = 0;
	double u2, u2Tilde;
	u2 = (u1 + u3) / 2;
	double deltaMinus, deltaPlus;
	double J1, J2, J3;
	double w;

	do {
		J1 = func(u1);
		J2 = func(u2);
		J3 = func(u3);
		deltaMinus = J1 - J2;
		deltaPlus = J3 - J3;
		w = u2 + (pow(u3 - u2, 2) * deltaMinus - pow(u2 - u1, 2) * deltaPlus) / 
			(2 * (u3 - u2) * deltaMinus + 2 * (u2 - u1) * deltaPlus);
		iter++;

		if (w < u2) {
			if (func(w) < J2) {
				u3 = u2;
				u2 = w;
			}
			else if (func(w) > J2) {
				u1 = w;
			}
			else if (func(w) == J2){
				if (J1 > J2) {
					u3 = u2;
					u2 = w;
				}
				else if (J2 > J3){
					u1 = w;
				}
			}

			//cout << "<<<\n";

		} else if (w > u2) {
			if (func(w) < J2) {
				u1 = u2;
				u2 = w;
			} else if (func(w) > J2) {
				u3 = w;
			} else if (func(w) == J2){
				if (J3 > J2) {
					u1 = u2;
					u2 = w;
				} else if (J1 > J2) {
					u3 = w;
				}
			}

			//cout << ">>>\n";

		}
		else {
			while (del >= eps) {
				if (func(u2 - del) < J2) {
					u2 = u2 - del;
					break;
				}
				else if (func(u2 + del) < J2) {
					u2 = u2 + del;
					break;
				}
				else {
					del /= 2;
				}
			}

			//cout << "===\n";

		}

		if (iter > 1000) {
			cout << "\nМаксимальное число итераций превышено";
			isFound = false;
			return 0;
		}
		//cout << u1 << ' ' << u2 << ' ' << u3 << '\n';

	} while (del >= eps);

	isFound = true;
	return u2;

}

double parabola(double a, double b, double del, double eps, int& iter) {
	int answer;
	bool isFound = false;

	cout << "\n\nМЕТОД ПАРАБОЛ: ";
	cout << "\nИзначально в методе используются следующие значения входных параметров:\na = " << a << ", b = " << b
		<< ", eps = " << eps << '\n';
	cout << "для их изменения введите 1, в противном случае введите 0\n";
	cin >> answer;
	if (answer == 1) {
		cout << "Введите значения a, b\n";
		cin >> a >> b >> eps;
	}

	
		double answerParabola = calcParabola(a, b, del, eps, iter, isFound);
		if (isFound) {
			cout << "\nрезультат работы метода (значение точки минимума): " << answerParabola;
			cout << "\nколичество итераций: " << iter;
			return answerParabola;
		}
		else {
			cout << "\nРешение не найдено";
		}

	return 0;
}

double findStartPositionForNewton(double a, double b) {

	double alpha = (sqrt(5) - 1) / 2;
	double alpha1 = (3 - sqrt(5)) / 2;
	double u1, u2, J1, J2;

	int i = 0;
	while (i < 3) {

		i++;

		u1 = a + alpha1 * (b - a);
		u2 = a + alpha * (b - a);
		J1 = func(u1);
		J2 = func(u2);
		if (J1 < J2) {
			b = u2;
			u2 = u1;
			J2 = J1;
			u1 = a + alpha1 * (b - a);
			J1 = func(u1);
		}
		else if (J1 > J2) {
			a = u1;
			u1 = u2;
			J1 = J2;
			u2 = a + alpha * (b - a);
			J2 = func(u2);
		}
		else {
			b = u2;
			a = u1;
			u1 = a + alpha1 * (b - a);
			u2 = a + alpha * (b - a);
			J1 = func(u1);
			J2 = func(u2);
		}

	}
	
	cout << "\nНачальная точка u_0 = " << (a + b) / 2 << '\n';
	return (a + b) / 2;

}

double calcMethodNewton(double& u, double eps, int& iter, bool& isFound) {

	double deriv;
	isFound = false;

	do {

		deriv = derivFunc(u);
		if (abs(deriv) <= eps) {
			isFound = true;
			return u;
		}
		else {
			double doubleDerive = doubleDerivFunc(u);
			if (doubleDerive > 0) {
				u = u - deriv / doubleDerive;
				iter++;
			}
			else {
				cout << "\nВычислить корень нельзя, ввиду несоответствия условию выпуклости\n";
				return 0;
			}
		}

		cout << u << '\n';

	} while (true);

}

double methodNewton(double a, double b, double eps, int& iter) {

	int answer;
	bool isFound = false;

	cout << "\n\nМЕТОД НЬЮТОНА:\n";
	cout << "Изначально в методе используются следующие значения входных параметров:\na = " << a << ", b = " << b
		<< ", eps = " << eps << '\n';
	cout << "для их изменения введите 1, в противном случае введите 0\n";
	cin >> answer;
	if (answer == 1) {
		cout << "Введите значения a, b, del\n";
		cin >> a >> b;
	}

	double startPosition = findStartPositionForNewton(a, b);
	double answerNewton = calcMethodNewton(startPosition, eps, iter, isFound);
	if (isFound) {
		cout << "\nрезультат работы метода (значение точки минимума): " << answerNewton;
		cout << "\nколичество итераций: " << iter;
	}
	else {
		cout << "Решение не найдено";
	}
	
	return answerNewton;

}

int main() {

	int iterDivideInterval = 0, iterGoldRatio = 0, iterParabola = 0, iterNewton = 0;
	setlocale(LC_ALL, "Russian");
	double a = -2, b = 2, del = 0.1, eps = 0.01;
	cout << "Вычисление точек минимума\n\n";

	if (isUnimodal(a, b, eps)) {
		double answerDivideInterval = divideInterval(a, b, del, eps, iterDivideInterval);
		double answerGoldRatio = goldRatio(a, b, eps, iterGoldRatio);
		double answerParabolaMethod = parabola(a, b, del, eps, iterParabola);
		double answerNewton = methodNewton(a, b, eps, iterNewton);
	}



	return 0;
}