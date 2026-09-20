#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

bool insertAtPosition(Node*& head, int value, int position) {
    if (position < 1)
    {
        return false;
    }
    Node* newNode = new Node(value);
    if (position == 1)
    {
        newNode->next = head;
        head = newNode;
        return true;
    }
    Node* current = head;
    int index = 1;
    while (current != nullptr && index < position - 1)
    {
        current = current->next;
        index++;
    }
    if (current == nullptr)
    {
        delete newNode;
        return false;
    }
    newNode->next = current->next;
    current->next = newNode;
    return true;
}

bool deleteAtPosition(Node*& head, int position) {
    if (head == nullptr || position < 1)
    {
        return false;
    }
    if (position == 1)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    Node* previous = head;
    int index = 1;
    while (previous->next != nullptr && index < position - 1)
    {
        previous = previous->next;
        index++;
    }
    if (previous->next == nullptr)
    {
        return false;
    }
    Node* target = previous->next;
    previous->next = target->next;
    delete target;
    return true;
}

int deleteByValue(Node*& head, int value, bool removeAll) {
    int removed = 0;
    while (head != nullptr && head->data == value)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        removed++;
        if (!removeAll)
        {
            return removed;
        }
    }
    Node* current = head;
    while (current != nullptr && current->next != nullptr)
    {
        if (current->next->data == value)
        {
            Node* target = current->next;
            current->next = target->next;
            delete target;
            removed++;
            if (!removeAll)
            {
                return removed;
            }
        }
        else
        {
            current = current->next;
        }
    }
    return removed;
}

Node* reverseList(Node* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 1)
    {
        return head;
    }
    if (k <= 0)
    {
        Node* previous = nullptr;
        Node* current = head;
        while (current != nullptr)
        {
            Node* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        return previous;
    }
    int length = 0;
    for (Node* probe = head; probe != nullptr; probe = probe->next)
    {
        length++;
    }
    Node dummy(0);
    dummy.next = head;
    Node* groupPrev = &dummy;
    while (length >= k)
    {
        Node* groupStart = groupPrev->next;
        Node* cursor = groupStart->next;
        for (int i = 1; i < k; i++)
        {
            groupStart->next = cursor->next;
            cursor->next = groupPrev->next;
            groupPrev->next = cursor;
            cursor = groupStart->next;
        }
        groupPrev = groupStart;
        length -= k;
    }
    return dummy.next;
}

Node* findMiddle(Node* head, bool secondMiddleForEven) {
    if (head == nullptr)
    {
        return nullptr;
    }
    if (head->next == nullptr)
    {
        return head;
    }
    Node* slow = head;
    Node* fast = head;
    Node* slowPrev = nullptr;
    while (fast != nullptr && fast->next != nullptr)
    {
        slowPrev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if (fast == nullptr && !secondMiddleForEven)
    {
        return slowPrev;
    }
    return slow;
}

bool removeCycle(Node* head) {
    if (head == nullptr || head->next == nullptr)
    {
        return false;
    }
    Node* slow = head;
    Node* fast = head;
    bool found = false;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        return false;
    }
    slow = head;
    if (slow == fast)
    {
        while (fast->next != slow)
        {
            fast = fast->next;
        }
        fast->next = nullptr;
        return true;
    }
    while (slow->next != fast->next)
    {
        slow = slow->next;
        fast = fast->next;
    }
    fast->next = nullptr;
    return true;
}

Node* mergeSortedLists(Node* first, Node* second) {
    if (first == nullptr)
    {
        return second;
    }
    if (second == nullptr)
    {
        return first;
    }
    Node dummy(0);
    Node* tail = &dummy;
    while (first != nullptr && second != nullptr)
    {
        if (first->data <= second->data)
        {
            tail->next = first;
            first = first->next;
        }
        else
        {
            tail->next = second;
            second = second->next;
        }
        tail = tail->next;
    }
    if (first != nullptr)
    {
        tail->next = first;
    }
    else
    {
        tail->next = second;
    }
    return dummy.next;
}

int removeDuplicates(Node* head, bool isSorted) {
    int removed = 0;
    if (head == nullptr || head->next == nullptr)
    {
        return removed;
    }
    if (isSorted)
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            if (current->data == current->next->data)
            {
                Node* duplicate = current->next;
                current->next = duplicate->next;
                delete duplicate;
                removed++;
            }
            else
            {
                current = current->next;
            }
        }
        return removed;
    }
    for (Node* outer = head; outer != nullptr; outer = outer->next)
    {
        Node* inner = outer;
        while (inner->next != nullptr)
        {
            if (inner->next->data == outer->data)
            {
                Node* duplicate = inner->next;
                inner->next = duplicate->next;
                delete duplicate;
                removed++;
            }
            else
            {
                inner = inner->next;
            }
        }
    }
    return removed;
}

Node* rotateLeft(Node* head, int k) {
    if (head == nullptr || head->next == nullptr || k <= 0)
    {
        return head;
    }
    int length = 1;
    Node* tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
        length++;
    }
    k = k % length;
    if (k == 0)
    {
        return head;
    }
    Node* newTail = head;
    for (int i = 1; i < k; i++)
    {
        newTail = newTail->next;
    }
    Node* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;
    return newHead;
}

bool deleteNthFromEnd(Node*& head, int n) {
    if (head == nullptr || n <= 0)
    {
        return false;
    }
    Node dummy(0);
    dummy.next = head;
    Node* lead = &dummy;
    Node* trail = &dummy;
    for (int i = 0; i < n; i++)
    {
        lead = lead->next;
        if (lead == nullptr)
        {
            return false;
        }
    }
    while (lead->next != nullptr)
    {
        lead = lead->next;
        trail = trail->next;
    }
    Node* target = trail->next;
    trail->next = target->next;
    delete target;
    head = dummy.next;
    return true;
}

int main() {
    auto build = [](const int* values, int size) -> Node*
    {
        Node* head = nullptr;
        Node* tail = nullptr;
        for (int i = 0; i < size; i++)
        {
            Node* node = new Node(values[i]);
            if (head == nullptr)
            {
                head = node;
                tail = node;
            }
            else
            {
                tail->next = node;
                tail = node;
            }
        }
        return head;
    };

    auto show = [](const char* label, Node* head)
    {
        cout << label << ": ";
        if (head == nullptr)
        {
            cout << "empty" << endl;
            return;
        }
        for (Node* current = head; current != nullptr; current = current->next)
        {
            cout << current->data;
            if (current->next != nullptr)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    };

    auto freeList = [](Node*& head)
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    };

    Node* list1 = nullptr;
    insertAtPosition(list1, 10, 1);
    insertAtPosition(list1, 30, 2);
    insertAtPosition(list1, 20, 2);
    insertAtPosition(list1, 5, 1);
    insertAtPosition(list1, 40, 5);
    cout << (insertAtPosition(list1, 99, 10) ? "inserted" : "invalid position") << endl;
    show("1. Insert", list1);

    deleteAtPosition(list1, 1);
    deleteAtPosition(list1, 4);
    deleteAtPosition(list1, 2);
    cout << (deleteAtPosition(list1, 9) ? "deleted" : "invalid position") << endl;
    show("2. Delete at position", list1);
    freeList(list1);
    cout << (deleteAtPosition(list1, 1) ? "deleted" : "empty list") << endl;

    int a3[] = {1, 2, 3, 2, 4, 2, 5};
    Node* list3 = build(a3, 7);
    cout << "3. Removed first 2: " << deleteByValue(list3, 2, false) << endl;
    cout << "   Removed remaining 2s: " << deleteByValue(list3, 2, true) << endl;
    cout << "   Removed head 1: " << deleteByValue(list3, 1, true) << endl;
    cout << "   Removed missing 99: " << deleteByValue(list3, 99, true) << endl;
    show("   Result", list3);
    freeList(list3);

    int a4[] = {1, 2, 3, 4, 5, 6, 7};
    Node* list4 = build(a4, 7);
    list4 = reverseList(list4, 0);
    show("4. Full reverse", list4);
    list4 = reverseList(list4, 3);
    show("   Reverse in groups of 3", list4);
    list4 = reverseList(list4, 1);
    show("   k = 1 (unchanged)", list4);
    freeList(list4);

    int a5[] = {1, 2, 3, 4, 5};
    int b5[] = {1, 2, 3, 4, 5, 6};
    Node* odd = build(a5, 5);
    Node* even = build(b5, 6);
    Node* single = build(a5, 1);
    Node* none = nullptr;
    cout << "5. Middle (odd): " << findMiddle(odd, true)->data << endl;
    cout << "   Middle (even, second): " << findMiddle(even, true)->data << endl;
    cout << "   Middle (even, first): " << findMiddle(even, false)->data << endl;
    cout << "   Middle (single): " << findMiddle(single, true)->data << endl;
    cout << "   Middle (empty): " << (findMiddle(none, true) == nullptr ? "none" : "found") << endl;
    freeList(odd);
    freeList(even);
    freeList(single);

    int a6[] = {1, 2, 3, 4, 5, 6};
    Node* list6 = build(a6, 6);
    Node* tail6 = list6;
    while (tail6->next != nullptr)
    {
        tail6 = tail6->next;
    }
    tail6->next = list6->next->next;
    cout << "6. Cycle in middle removed: " << (removeCycle(list6) ? "yes" : "no") << endl;
    show("   Result", list6);
    tail6 = list6;
    while (tail6->next != nullptr)
    {
        tail6 = tail6->next;
    }
    tail6->next = list6;
    cout << "   Cycle at head removed: " << (removeCycle(list6) ? "yes" : "no") << endl;
    show("   Result", list6);
    cout << "   No cycle present: " << (removeCycle(list6) ? "removed" : "nothing to remove") << endl;
    freeList(list6);

    int a7[] = {1, 3, 5, 7};
    int b7[] = {2, 4, 6, 8, 10};
    Node* left = build(a7, 4);
    Node* right = build(b7, 5);
    Node* merged = mergeSortedLists(left, right);
    show("7. Merged sorted lists", merged);
    Node* mergedWithEmpty = mergeSortedLists(merged, nullptr);
    show("   Merged with empty", mergedWithEmpty);
    freeList(mergedWithEmpty);

    int a8[] = {1, 1, 2, 3, 3, 3, 4};
    int b8[] = {4, 2, 4, 1, 2, 5, 1};
    Node* sortedList = build(a8, 7);
    Node* unsortedList = build(b8, 7);
    cout << "8. Sorted duplicates removed: " << removeDuplicates(sortedList, true) << endl;
    show("   Result", sortedList);
    cout << "   Unsorted duplicates removed: " << removeDuplicates(unsortedList, false) << endl;
    show("   Result", unsortedList);
    freeList(sortedList);
    freeList(unsortedList);

    Node* list9 = build(a5, 5);
    list9 = rotateLeft(list9, 2);
    show("9. Rotate left by 2", list9);
    list9 = rotateLeft(list9, 7);
    show("   Rotate left by 7", list9);
    list9 = rotateLeft(list9, 5);
    show("   Rotate left by 5 (full turn)", list9);
    freeList(list9);

    Node* list10 = build(a5, 5);
    deleteNthFromEnd(list10, 2);
    show("10. Delete 2nd from end", list10);
    deleteNthFromEnd(list10, 4);
    show("    Delete head (4th from end)", list10);
    deleteNthFromEnd(list10, 1);
    show("    Delete last node", list10);
    cout << "    Out of range: " << (deleteNthFromEnd(list10, 9) ? "deleted" : "invalid") << endl;
    freeList(list10);

    return 0;
}