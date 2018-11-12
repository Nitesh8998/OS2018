""" SImulation of Banking Synchronisation Problem """

import threading
import random
import time
import numpy as np

OVERALL_BAL = 100000
MIN_OVER_BAL = 10000
MIN_BAL = 10000
MAX_CUST = 5

MUTEX = threading.BoundedSemaphore(1)
TOKEN = 0

RAND_TRANS_ID = np.arange(1, 211)


class Counter(object):
    """docstring for Counter"""

    def __init__(self, number):
        super(Counter, self).__init__()
        self.sem = threading.BoundedSemaphore(1)
        self.number = number

    def takes_in(self, customer, trans_id):
        """ COunter accepts a customer """
        self.sem.acquire()

        print("counter %d takes customer with cust_id: and acquires the counter sem" % (
            self.number, customer.cust_id))

    def do_stuff(self, customer, trans_id):
        """ FOr doing stuff """

        debt_or_cred = debt_cred()
        rand_amnt = random.randrange(10000, 50000, 1000)

        if debt_or_cred:
            status = customer.debit(rand_amnt, trans_id)
            if status != True:
                print("Customer with cust_id: %d has acnt_bal:%d cannot draw %d" % (
                    customer.cust_id, customer.acnt_bal, rand_amnt))

        else:
            customer.credit(rand_amnt, trans_id)
        # trans

        time.sleep(2)

    def take_out(self, customer, trans_id):
        """ for releasing the customer """

        de_assign_tid(trans_id)

        print("counter %d kicks customer with cust_id: and acquires the counter sem" % (
            self.number, customer.cust_id))

        self.sem.release()


class Customer(object):
    """docstring for Customer"""

    def __init__(self, acnt_bal, cust_id):
        super(Customer, self).__init__()
        self.acnt_bal = acnt_bal
        self.cust_id = cust_id
        self.counter_no = 0

    def debit(self, amnt, trans_id):
        """ for debit Operation """
        global OVERALL_BAL
        MUTEX.acquire()

        truth = False

        if self.acnt_bal - amnt < MIN_BAL and OVERALL_BAL - amnt < MIN_OVER_BAL:
            truth = False

        else:
            self.acnt_bal -= amnt
            OVERALL_BAL -= amnt
            print(" debit was succesful for trans_id: %d and cust_id: %d with new acnt_bal:%d" % (
                trans_id, self.cust_id, self.acnt_bal))
            truth = True

        MUTEX.release()

        return truth

    def credit(self, amnt, trans_id):
        """ For credit operation """

        global OVERALL_BAL

        MUTEX.acquire()

        self.acnt_bal += amnt
        OVERALL_BAL += amnt

        print(" credit was succesful for trans_id: %d and cust_id: %d with new acnt_bal:%d" % (
            trans_id, self.cust_id, self.acnt_bal))

        MUTEX.release()

    def print_details(self):

        print("Customer id:%d  acnt_bal:%d " % (self.cust_id, self.acnt_bal))


def assign_tid():
    """ Giving a random transaction id from the list"""

    while 1:
        ran = random.randrange(1, 211, 1)
        if RAND_TRANS_ID[ran] == 0:
            MUTEX.acquire()
            RAND_TRANS_ID[ran] = 1
            MUTEX.release()
            return ran


def de_assign_tid(ran):
    """ making the transaction id open again """

    MUTEX.acquire()
    RAND_TRANS_ID[ran] = 0
    MUTEX.release()


def debt_cred():
    """ Debt = 1 Cred is 0 """
    return random.randint(0, 1)


def counter_handler(counter):
    """ driver for counters"""

    print("Counter %d became active" % counter.number)

    while 1:
        pass


def customer_handler(customer):
    """ Driver for Customers"""
    pass


def main():
    customers = []
    counters = []
    # threads_counters = []
    threads_customer = []

    for i in range(0, 3):
        counters.append(Counter(i))

    for i in range(0, MAX_CUST):
        customers.append(Customer(random.randrange(10000, 100000, 10000), i+1))
        pass

    for i in range(0, MAX_CUST):
        customers[i].print_details()

    # for i in range(0, MAX_CUST):
        # threads.append(threading.Thread(target =customer_handler,args=customer[i]))

    print(RAND_TRANS_ID)
    print(counters)


if __name__ == '__main__':
    main()
