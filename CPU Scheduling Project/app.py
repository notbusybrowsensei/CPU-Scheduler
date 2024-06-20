from flask import Flask, render_template, request
import subprocess
import re

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/schedule', methods=['POST'])
def schedule():
    algorithm = request.form['algorithm']
    n = int(request.form['n'])
    quantum = request.form.get('quantum', '')

    arrival_times = request.form.getlist('arrival_time')
    serve_times = request.form.getlist('serve_time')
    priorities = request.form.getlist('priority')

    input_data = f"{n}\n"
    for i in range(n):
        if algorithm == "priority":
            input_data += f"{arrival_times[i]} {serve_times[i]} {priorities[i]}\n"
        else:
            input_data += f"{arrival_times[i]} {serve_times[i]}\n"
    if algorithm == "round_robin":
        input_data += f"{quantum}\n"

    try:
        process = subprocess.Popen(['./scheduler', algorithm], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        output, error = process.communicate(input=input_data)
        if error:
            return f"Error: {error}"

        processes = []
        total_serve_time = 0
        average_waiting_time = 0.0
        output_lines = output.strip().split('\n')

        for line in output_lines:
            match = re.match(r'P(\d+):\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)', line.strip())
            if match:
                process = {
                    'id': int(match.group(1)),
                    'arrival_time': int(match.group(2)),
                    'serve_time': int(match.group(3)),
                    'finish_time': int(match.group(4)),
                    'response_time': int(match.group(5)),
                    'waiting_time': int(match.group(6))
                }
                total_serve_time += process['serve_time']
                average_waiting_time += process['waiting_time']
                processes.append(process)

        average_waiting_time /= n

        total_time = max(p['finish_time'] for p in processes)
        throughput = n / total_time

        cpu_utilization = (total_serve_time / total_time) * 100

        processes.sort(key=lambda x: x['finish_time'])

        return render_template('result.html', output=processes, average_waiting_time=average_waiting_time, throughput=throughput, cpu_utilization=cpu_utilization)

    except Exception as e:
        return f"Execution failed: {str(e)}"

if __name__ == '__main__':
    app.run(debug=True)




















