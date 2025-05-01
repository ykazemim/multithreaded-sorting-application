# Multithreaded Array Sorter in C

This C program demonstrates the use of **POSIX threads (pthreads)** to perform a **parallel sort** on an array using the **Bubble Sort** algorithm, followed by a **merge** step.

## 🔧 Features

- Uses **two threads** to sort two halves of an array in parallel.
- Merges the sorted halves using a **third thread**.
- Efficiently demonstrates **multithreaded programming** basics in C.
- Accepts user input and handles input validation.

## 🧠 How It Works

1. The user enters an **even-sized** array.
2. The array is divided into two halves.
3. Each half is sorted using `bubble_sort` in a separate thread.
4. A third thread merges the two sorted halves into a final sorted array.

## 🤝 Contributing

Feel free to fork, modify, or contribute!
