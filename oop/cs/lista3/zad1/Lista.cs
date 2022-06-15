using System;

namespace Lista
{
    public class MyList<T> {
        class ListItem  {
            public T value;
            public ListItem next;
            public ListItem prev;

            public ListItem(T value)
            {
                this.value = value;
                next = null;
                prev = null;
            }
        }
        ListItem first;

        public MyList() {
            first = null;
        }

        public bool is_empty() {
            return first == null;
        }

        public void push_front(T elem) {
            ListItem item = new ListItem(elem);

            if (is_empty()) {
                first = item;
                return;
            }

            if (first.next == null)
            {
                item.next = first;
                item.prev = first;
                first.prev = item;
                first = item;
                return;
            }

            item.next = first;
            item.prev = first.prev;
            first.prev = item;
            first = item;
        }

        public void push_back(T elem) {
            ListItem item = new ListItem(elem);

            if (is_empty()) {
                first = item;
                return;
            }

            if (first.next == null) {
                item.prev = first;
                first.prev = item;
                first.next = item;
                return;
            } else {
                item.prev = first.prev;
                first.prev.next = item;
                first.prev = item;
            }

        }

        public T pop_front() {
            if (is_empty()) {
                throw new Exception("list is empty");
            }
            
            T temp = first.value;
            if (first.next == null) {
                first = null;
            } else {
                first.next.prev = first.prev;
                first = first.next;
            }
            return temp; 
        }

        public T pop_back() {
            if (is_empty()) {
                throw new Exception("list is empty");
            }

            T temp = first.value;
            if (first.next == null) {
                first = null;
            } else {
                first.prev = first.prev.prev;
                first.prev.next = null;
            }
            return temp;
        }

        public void print() {
            ListItem temp = first;
            while (temp != null) {
                Console.Write(temp.value + " ");
                temp = temp.next;
            }
            Console.WriteLine();
        }
    }
}