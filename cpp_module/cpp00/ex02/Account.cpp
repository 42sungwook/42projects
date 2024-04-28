#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
		: _accountIndex(_nbAccounts), _amount(initial_deposit),
			_nbDeposits(0), _nbWithdrawals(0) {
	_nbAccounts++;
	_totalAmount += _amount;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account() {
	_nbAccounts--;
	_totalAmount -= _amount;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
}

int Account::getNbAccounts() {
	return _nbAccounts;
}

int Account::getTotalAmount() {
	return _totalAmount;
}

int Account::getNbDeposits() {
	return _totalNbDeposits;
}

int Account::getNbWithdrawals() {
	return _totalNbWithdrawals;
}

void Account::displayAccountsInfos() {
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";total:" << _totalAmount << ";deposits:" << 
	_totalNbDeposits << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void Account::makeDeposit(int deposit) {
	_totalAmount += deposit;
	_amount += deposit;
	_nbDeposits++;
	_totalNbDeposits++;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_amount:" << _amount - deposit << 
	";deposit:" << deposit << ";amount:" << _amount << ";nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
	if (withdrawal <= _amount) {
		_totalAmount -= withdrawal;
		_amount -= withdrawal;
		_nbWithdrawals++;
		_totalNbWithdrawals++;

		_displayTimestamp();
		std::cout << "index:" << _accountIndex << ";p_amount:" << _amount + withdrawal <<
		";withdrawal:" << withdrawal << ";amount:" << _amount << ";nb_withdrawals:" << 
		_nbWithdrawals << std::endl;

		return true;
	} else {
		_displayTimestamp();
		std::cout << "index:" << _accountIndex << ";p_amount:" << _amount << 
		";withdrawal:refused" << std::endl;

		return false;
	}
}

int Account::checkAmount() const {
	return _amount;
}

void Account::displayStatus() const {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";deposits:" << 
	_nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
}

void Account::_displayTimestamp() {
	std::time_t currentTime = std::time(NULL);
	std::tm* localTime = std::localtime(&currentTime);

	std::cout << std::setfill('0');
	std::cout << "[" << localTime->tm_year + 1900
						<< std::setw(2) << localTime->tm_mon + 1
						<< std::setw(2) << localTime->tm_mday << "_"
						<< std::setw(2) << localTime->tm_hour
						<< std::setw(2) << localTime->tm_min
						<< std::setw(2) << localTime->tm_sec << "] ";
}
