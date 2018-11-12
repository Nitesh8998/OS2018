""" SImulation of Banking Synchronisation Problem """

import threading
import random
import time
import numpy as np

OVERALL_BAL = 100000
MIN_OVER_BAL = 10000
MIN_BAL = 10000
MAX_CUST = 10
NUM_COUNTERS = 4

MUTEX = threading.BoundedSemaphore(1)

# MUTEX = threading.Lock()
TOKEN = 0

# RAND_TRANS_ID = np.arange(1, 212)

RAND_TRANS_ID = [0] * 212


class Counter(object):
    """doc string for Counter"""

    def __init__(self, number):
        super(Counter, self).__init__()
        self.sem = threading.BoundedSemaphore(1)
        self.number = number

    def takes_in(self, customer, trans_id):
        """ COunter accepts a customer """
        self.sem.acquire()

        print("counter %d takes customer with cust_id:%d and trans_id:%d acquires the counter sem" % (
            self.number, customer.cust_id, trans_id))

    def do_stuff(self, customer, trans_id):
        """ FOr doing stuff """

        debt_or_cred = debt_cred()
        rand_amnt = random.randrange(10000, 50000, 1000)

        if debt_or_cred:
            status = customer.debit(rand_amnt, trans_id)
            if status is False:
                print("Customer with cust_id: %d has acnt_bal:%d cannot draw %d" % (
                    customer.cust_id, customer.acnt_bal, rand_amnt))

        else:
            customer.credit(rand_amnt, trans_id)
        # trans

        # time.sleep(2)

    def take_out(self, customer, trans_id):
        """ for releasing the customer """

        de_assign_tid(trans_id)

        print("counter %d kicks customer with cust_id:%d and releases the counter sem \n" % (
            self.number, customer.cust_id))

        self.sem.release()
        time.sleep(1)


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
        print(" before debit for trans_id: %d and cust_id: %d with new acnt_bal:%d" % (
            trans_id, self.cust_id, self.acnt_bal))

        truth = False

        if self.acnt_bal - amnt < MIN_BAL and OVERALL_BAL - amnt < MIN_OVER_BAL:
            truth = False

        elif self.acnt_bal - amnt < MIN_BAL:
            truth = False

        else:
            self.acnt_bal -= amnt
            OVERALL_BAL -= amnt
            print("This is the amount to be debited", amnt)
            print(" debit was successful for trans_id: %d and cust_id: %d with new acnt_bal:%d" % (
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
        print("This is the amnt to be credited", amnt)
        print(" credit was succesful for trans_id: %d and cust_id: %d with new acnt_bal:%d" % (
            trans_id, self.cust_id, self.acnt_bal))

        MUTEX.release()

    def print_details(self):

        print("Customer id:%d  acnt_bal:%d " % (self.cust_id, self.acnt_bal))


def assign_tid():
    """ Giving a random transaction id from the list"""
    # print("going for tid")
    global MUTEX
    MUTEX.acquire()
    # print("got lock")

    while 1:
        ran = random.randrange(1, 211, 1)
        if RAND_TRANS_ID[ran] == 0:
            
            RAND_TRANS_ID[ran] = 1
            break
    # print("got tid")
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


def customer_handler(customer, counters):
    """ Driver for Customers"""
    print(" Customer with customer details")
    customer.print_details()
    print(" is looking for counter")

    global TOKEN
    i = 0
    while 1:
        # print("Went in")
        trans_id = assign_tid()
        MUTEX.acquire()
        TOKEN += 1
        print("token increased",end=" ")
        print(TOKEN)
        MUTEX.release()

        counter_num = TOKEN % NUM_COUNTERS

        counters[counter_num].takes_in(customer, trans_id)
        counters[counter_num].do_stuff(customer, trans_id)
        counters[counter_num].take_out(customer, trans_id)
        # i += 1
        # print("came back")

    pass


def main():
    customers = []
    counters = []
    # threads_counters = []
    threads_customer = []

    for i in range(0, NUM_COUNTERS):
        counters.append(Counter(i))

    for i in range(0, MAX_CUST):
        customers.append(Customer(random.randrange(10000, 100000, 10000), i+1))
        pass

    for i in range(0, MAX_CUST):
        customers[i].print_details()

    print(RAND_TRANS_ID)

    for i in range(0, MAX_CUST):
        threads_customer.append(threading.Thread(target =customer_handler,args=(customers[i], counters)))
        threads_customer[-1].start()

    for i in range(0, MAX_CUST):
        threads_customer[i].join()
        pass

    print(RAND_TRANS_ID)
    print(counters)


if __name__ == '__main__':
    main()
