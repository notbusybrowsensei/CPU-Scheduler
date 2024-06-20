# CPU-Scheduler

## Project Description

A **CPU scheduler** with a proper frontend consisting of multiple algorithms such as :

- **First Come First Serve(FCFS)**
- **Priority Scheduling(lower number -> higher priority)**
- **Shortest Job First(SJF)**
- **Round Robin(RR)**

The given project displays proper scheduling of the procceses, average waiting time, throughput and CPU utilization. It also shows tabular data for each process showing its response time, finish time, waiting time, etc.

## Installation

  **1.** Clone the github repository: Run the following command in your terminal.
   ```
   git clone https://github.com/notbusybrowsensei/CPU-Scheduler.git
   ```
  **2.** Navigate to the respective directory.
   ```
   cd CPU-Scheduler
   ```
   Then navigate to
   ```
   cd CPU Scheduling Project
   ```
  **3.** Install the dependencies
   ```
   pip install -r requirements.txt
   ```

## Usage

  **1.** For accessing the website, run:
  ```
  python app.py
  ```
  **2.** The website will be accessible on `http://127.0.0.1:5000` 
  
  **3.** Select any algorithm and enter the total number of processes and their corresponding entries and press Submit.
  
## Output 

- Tabular data containing response time,waiting time, finish time.
- Gantt chart (for checking the processes ID in the gantt chart you need to hover over the line segments)
- Performance metrics like average waiting time,throughput and CPU utilization.

## Internal Working

- Utilizes various algorithms to dynamically allocate CPU resources to processes based on their characteristics.
- Implements FCFS, Priority, SJF, and Round Robin algorithms to optimize process execution and resource utilization.
- Provides intuitive Gantt chart visualization of process execution timelines, aiding in understanding scheduling decisions.
- Computes metrics such as average waiting time, throughput, and CPU utilization to assess system performance dynamically.
- Manages process queues effectively to ensure fair and efficient CPU allocation, adhering to algorithmic principles.
- Flask application serves as an interface to interact with the C++ executable. The application handles HTTP requests, executes the C++ program, and processes the output for display.

## References

- https://www.youtube.com/playlist?list=PLBlnK6fEyqRitWSE_AyyySWfhRgyA-rHk






