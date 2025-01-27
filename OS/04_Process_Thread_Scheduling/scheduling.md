# CPU 스케줄링 (CPU Scheduling)

## A. CPU 스케줄링의 기본 개념
ㄴ
CPU 스케줄링은 운영체제가 프로세스들 간에 CPU 자원을 효율적으로 할당하는 메커니즘입니다. 시스템의 전반적인 성능과 사용자 경험에 직접적인 영향을 미치는 핵심적인 기능입니다.

### 1. 스케줄링의 목표

스케줄링은 다음과 같은 여러 목표를 달성하기 위해 수행됩니다:

```mermaid
graph TD
    subgraph "스케줄링 목표"
        A[CPU 활용도 최대화] --> D[시스템 성능]
        B[처리량 향상] --> D
        C[응답 시간 최소화] --> D
        
        E[공정성 보장] --> F[사용자 만족도]
        G[우선순위 준수] --> F
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

### 2. 스케줄링이 발생하는 상황

프로세스 스케줄링은 다음과 같은 상황에서 발생합니다:

```mermaid
stateDiagram-v2
    [*] --> Running
    Running --> Ready: 1. 타임 퀀텀 만료
    Running --> Waiting: 2. I/O 요청
    Waiting --> Ready: 3. I/O 완료
    Ready --> Running: 4. 스케줄러 선택
    Running --> Terminated: 5. 프로세스 종료
    
    note right of Running
        CPU 실행 중
    end note
```

### 3. 스케줄링 기준

스케줄링 결정을 내릴 때 고려하는 주요 기준들입니다:

1. CPU 활용도 (CPU Utilization)
   - CPU가 유휴 상태에 있는 시간을 최소화
   - 가능한 한 CPU를 바쁘게 유지

2. 처리량 (Throughput)
   - 단위 시간당 완료되는 프로세스의 수
   - 시스템의 전체적인 작업 처리 능력 측정

3. 총처리 시간 (Turnaround Time)
   - 프로세스가 시작부터 종료까지 걸리는 총 시간
   - 대기 시간과 실행 시간의 합

4. 대기 시간 (Waiting Time)
   - 프로세스가 준비 큐에서 대기하는 시간의 합
   - 짧을수록 좋음

5. 응답 시간 (Response Time)
   - 요청 후 첫 응답이 출력되기까지 걸리는 시간
   - 대화형 시스템에서 특히 중요

## B. 기본 스케줄링 알고리즘

### 1. 선입선출 스케줄링 (FCFS: First-Come, First-Served)

가장 단순한 스케줄링 알고리즘으로, 먼저 도착한 프로세스를 먼저 처리합니다.

```mermaid
gantt
    title FCFS 스케줄링 예시
    dateFormat X
    axisFormat %s
    
    section 프로세스
    P1 :0, 5
    P2 :5, 3
    P3 :8, 4
```

구현 예제:
```c
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void fcfs_scheduling(Process processes[], int n) {
    // 도착 시간 순으로 정렬
    sort(processes, processes + n, 
         [](const Process& a, const Process& b) {
             return a.arrival_time < b.arrival_time;
         });
    
    int current_time = 0;
    
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        processes[i].waiting_time = 
            current_time - processes[i].arrival_time;
            
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;
        
        processes[i].turnaround_time = 
            processes[i].completion_time - 
            processes[i].arrival_time;
    }
}
```

### 2. 최단 작업 우선 스케줄링 (SJF: Shortest Job First)

실행 시간이 가장 짧은 프로세스를 우선적으로 처리하는 알고리즘입니다.

```mermaid
gantt
    title SJF 스케줄링 예시
    dateFormat X
    axisFormat %s
    
    section 프로세스
    P2 (2) :0, 2
    P4 (3) :2, 3
    P1 (4) :5, 4
    P3 (6) :9, 6
```

구현 예제:
```c
void sjf_scheduling(Process processes[], int n) {
    vector<Process> ready_queue;
    int current_time = 0;
    int completed = 0;
    
    while (completed < n) {
        // 현재 시간에 도착한 프로세스들을 레디 큐에 추가
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time &&
                !processes[i].completed) {
                ready_queue.push_back(processes[i]);
            }
        }
        
        if (ready_queue.empty()) {
            current_time++;
            continue;
        }
        
        // 가장 짧은 실행 시간을 가진 프로세스 선택
        auto shortest = min_element(
            ready_queue.begin(),
            ready_queue.end(),
            [](const Process& a, const Process& b) {
                return a.burst_time < b.burst_time;
            }
        );
        
        Process& current = *shortest;
        current.waiting_time = 
            current_time - current.arrival_time;
        current_time += current.burst_time;
        current.completion_time = current_time;
        current.turnaround_time = 
            current.completion_time - current.arrival_time;
        current.completed = true;
        
        completed++;
        ready_queue.erase(shortest);
    }
}
```

### 3. 라운드 로빈 스케줄링 (Round Robin)

각 프로세스에 동일한 시간 할당량(Time Quantum)을 부여하고 순환하며 실행하는 알고리즘입니다.

```mermaid
graph TD
    subgraph "라운드 로빈 실행"
        A[P1] --> B[P2]
        B --> C[P3]
        C --> D[P4]
        D --> A
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style B fill:#9cf,stroke:#333,stroke-width:2px
        style C fill:#9cf,stroke:#333,stroke-width:2px
        style D fill:#f9f,stroke:#333,stroke-width:2px
    end
```

구현 예제:
```c
void round_robin_scheduling(Process processes[], 
                          int n, 
                          int time_quantum) {
    queue<Process*> ready_queue;
    int current_time = 0;
    int completed = 0;
    
    // 초기 프로세스들을 큐에 추가
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time == 0) {
            ready_queue.push(&processes[i]);
        }
    }
    
    while (completed < n) {
        if (ready_queue.empty()) {
            current_time++;
            // 새로 도착한 프로세스 확인
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time == current_time) {
                    ready_queue.push(&processes[i]);
                }
            }
            continue;
        }
        
        Process* current = ready_queue.front();
        ready_queue.pop();
        
        int execution_time = min(time_quantum, 
                               current->remaining_time);
        current->remaining_time -= execution_time;
        current_time += execution_time;
        
        // 새로 도착한 프로세스들 확인
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time > current_time - execution_time &&
                processes[i].arrival_time <= current_time) {
                ready_queue.push(&processes[i]);
            }
        }
        
        if (current->remaining_time > 0) {
            ready_queue.push(current);
        } else {
            current->completion_time = current_time;
            current->turnaround_time = 
                current->completion_time - current->arrival_time;
            current->waiting_time = 
                current->turnaround_time - current->burst_time;
            completed++;
        }
    }
}
```

## C. 고급 스케줄링 알고리즘

### 1. 다단계 큐 스케줄링 (Multilevel Queue)

프로세스들을 여러 종류의 큐로 분류하여 각각 다른 스케줄링 알고리즘을 적용합니다.

```mermaid
graph TD
    subgraph "다단계 큐"
        A[시스템 프로세스] --> E[우선순위 1]
        B[대화형 프로세스] --> F[우선순위 2]
        C[배치 프로세스] --> G[우선순위 3]
        D[백그라운드 프로세스] --> H[우선순위 4]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style E fill:#9cf,stroke:#333,stroke-width:2px
        style H fill:#f9f,stroke:#333,stroke-width:2px
    end
```

구현 예제:
```c
class MultilevelQueue {
private:
    vector<queue<Process*>> queues;
    vector<int> priorities;
    vector<int> time_quantums;
    
public:
    MultilevelQueue(int num_levels) 
        : queues(num_levels),
          priorities(num_levels),
          time_quantums(num_levels) {}
    
    void add_process(Process* process, int level) {
        if (level >= 0 && level < queues.size()) {
            queues[level].push(process);
        }
    }
    
    Process* get_next_process() {
        // 높은 우선순위 큐부터 검사
        for (int i = 0; i < queues.size(); i++) {
            if (!queues[i].empty()) {
                Process* process = queues[i].front();
                queues[i].pop();
                return process;
            }
        }
        return nullptr;
    }
    
    void schedule() {
        int current_time = 0;
        
        while (true) {
            Process* current = get_next_process();
            if (!current) break;
            
            int level = current->priority_level;
            int quantum = time_quantums[level];
            
            // 프로세스 실행
            int execution_time = 
                min(quantum, current->remaining_time);
            current->remaining_time -= execution_time;
            current_time += execution_time;
            
            // 남은 시간이 있으면 다음 레벨 큐로 이동
            if (current->remaining_time > 0) {
                int next_level = min(level + 1, 
                                   (int)queues.size() - 1);
                add_process(current, next_level);
            }
        }
    }
};
```

### 2. 다단계 피드백 큐 스케줄링 (Multilevel Feedback Queue)

프로세스의 동작 특성에 따라 큐 간 이동이 가능한 유연한 스케줄링 알고리즘입니다. 각 큐는 서로 다른 우선순위와 시간 할당량을 가지며, 프로세스의 실행 특성에 따라 동적으로 큐를 이동할 수 있습니다.

```mermaid
stateDiagram-v2
    [*] --> Q0: 새 프로세스
    Q0 --> Q1: 타임 퀀텀 소진
    Q1 --> Q2: 타임 퀀텀 소진
    Q2 --> Q3: 타임 퀀텀 소진
    Q1 --> Q0: 우선순위 상승
    Q2 --> Q1: 우선순위 상승
    Q3 --> Q2: 우선순위 상승
    
    note right of Q0
        가장 높은 우선순위
        가장 짧은 타임 퀀텀
    end note
```

구현 예제:
```c
class MultilevelFeedbackQueue {
private:
    struct QueueLevel {
        queue<Process*> processes;
        int time_quantum;
        int priority;
    };
    
    vector<QueueLevel> levels;
    int aging_threshold;
    
public:
    MultilevelFeedbackQueue(int num_levels, 
                          int base_quantum,
                          int aging_threshold)
        : levels(num_levels), 
          aging_threshold(aging_threshold) {
        // 각 레벨별 타임 퀀텀 설정 (2의 거듭제곱)
        for (int i = 0; i < num_levels; i++) {
            levels[i].time_quantum = base_quantum * (1 << i);
            levels[i].priority = num_levels - i;
        }
    }
    
    void add_process(Process* process) {
        // 새로운 프로세스는 항상 최상위 큐에 배치
        levels[0].processes.push(process);
        process->current_level = 0;
        process->wait_time = 0;
    }
    
    void schedule() {
        while (true) {
            bool found_process = false;
            
            // 상위 큐부터 차례로 프로세스 탐색
            for (int i = 0; i < levels.size(); i++) {
                auto& level = levels[i];
                
                if (!level.processes.empty()) {
                    Process* current = level.processes.front();
                    level.processes.pop();
                    found_process = true;
                    
                    // 프로세스 실행
                    int executed_time = execute_process(
                        current, 
                        level.time_quantum
                    );
                    
                    if (current->remaining_time > 0) {
                        // 타임 퀀텀을 모두 사용한 경우
                        if (executed_time >= level.time_quantum) {
                            demote_process(current);
                        } else {
                            // I/O나 다른 이벤트로 인한 중단
                            promote_process(current);
                        }
                    }
                    
                    // 에이징 처리
                    handle_aging();
                    break;
                }
            }
            
            if (!found_process) break;
        }
    }
    
private:
    int execute_process(Process* process, int quantum) {
        int execution_time = min(
            process->remaining_time, 
            quantum
        );
        
        process->remaining_time -= execution_time;
        process->wait_time = 0;  // 실행했으므로 대기 시간 초기화
        
        return execution_time;
    }
    
    void promote_process(Process* process) {
        // 상위 큐로 이동 (우선순위 상승)
        int new_level = max(0, process->current_level - 1);
        process->current_level = new_level;
        levels[new_level].processes.push(process);
    }
    
    void demote_process(Process* process) {
        // 하위 큐로 이동 (우선순위 감소)
        int new_level = min(
            (int)levels.size() - 1, 
            process->current_level + 1
        );
        process->current_level = new_level;
        levels[new_level].processes.push(process);
    }
    
    void handle_aging() {
        // 모든 큐의 프로세스들의 대기 시간 증가
        for (auto& level : levels) {
            queue<Process*> temp = level.processes;
            while (!temp.empty()) {
                Process* process = temp.front();
                temp.pop();
                
                process->wait_time++;
                
                // 에이징 임계값을 초과한 경우 상위 큐로 이동
                if (process->wait_time >= aging_threshold) {
                    promote_process(process);
                    process->wait_time = 0;
                } else {
                    level.processes.push(process);
                }
            }
        }
    }
};
```

이 구현의 주요 특징:

1. 우선순위 관리
   - 각 레벨은 서로 다른 우선순위와 시간 할당량을 가짐
   - 상위 큐일수록 높은 우선순위와 짧은 시간 할당량
   - 하위 큐로 갈수록 긴 시간 할당량 부여

2. 동적 큐 이동
   - 프로세스가 시간 할당량을 모두 사용하면 하위 큐로 이동
   - I/O 바운드 프로세스는 상위 큐로 이동 가능
   - 에이징을 통한 기아 상태 방지

3. 에이징 처리
   - 오래 대기한 프로세스의 우선순위를 점진적으로 상승
   - 임계값 이상 대기한 프로세스는 상위 큐로 이동
   - 공정성 보장을 위한 메커니즘

4. 효율적인 실행 관리
   - 상위 큐에 있는 프로세스 우선 실행
   - 시간 할당량은 레벨이 낮아질수록 기하급수적으로 증가
   - 실행 이력에 따른 동적 우선순위 조정

## D. 현대 운영체제의 스케줄러

### 1. 리눅스 CFS (Completely Fair Scheduler)

CFS는 프로세스들 간의 CPU 시간을 공정하게 분배하는 것을 목표로 하는 리눅스의 기본 스케줄러입니다.

```mermaid
graph TD
    subgraph "CFS 구조"
        A[레드-블랙 트리] --> B[vruntime 기반 정렬]
        B --> C[실행 큐]
        
        D[nice 값] --> E[가중치 계산]
        E --> F[타임 슬라이스 조정]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style C fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

CFS 스케줄러 구현 예제:
```c
class CFScheduler {
private:
    struct rb_root tasks_timeline;  // 레드-블랙 트리
    unsigned long min_granularity;  // 최소 실행 단위
    
    // 가중치 테이블 (nice 값에 따른 가중치)
    static const int prio_to_weight[40] = {
        /* -20 */ 88761, 71755, 56483, 46273, 36291,
        /* -15 */ 29154, 23254, 18705, 14949, 11916,
        /* -10 */ 9548,  7620,  6100,  4904,  3906,
        /*  -5 */ 3121,  2501,  1991,  1586,  1277,
        /*   0 */ 1024,  820,   655,   526,   423,
        /*   5 */ 335,   272,   215,   172,   137,
        /*  10 */ 110,   87,    70,    56,    45,
        /*  15 */ 36,    29,    23,    18,    15
    };
    
public:
    CFScheduler(unsigned long granularity) 
        : min_granularity(granularity) {
        tasks_timeline = RB_ROOT;
    }
    
    void enqueue_task(struct task_struct* task) {
        // vruntime 계산
        unsigned long weight = get_task_weight(task);
        task->vruntime += min_granularity * (1024 / weight);
        
        // 레드-블랙 트리에 삽입
        rb_insert(&tasks_timeline, task);
    }
    
    struct task_struct* pick_next_task() {
        // 가장 작은 vruntime을 가진 태스크 선택
        struct rb_node* leftmost = rb_first(&tasks_timeline);
        if (!leftmost)
            return NULL;
            
        return rb_entry(leftmost, struct task_struct, node);
    }
    
    void task_tick(struct task_struct* curr) {
        unsigned long delta_exec;
        unsigned long weight;
        
        // 실행 시간 업데이트
        delta_exec = get_task_delta_exec(curr);
        curr->sum_exec_runtime += delta_exec;
        
        // vruntime 업데이트
        weight = get_task_weight(curr);
        curr->vruntime += delta_exec * (1024 / weight);
        
        // 필요한 경우 재스케줄링
        if (need_resched(curr))
            set_tsk_need_resched(curr);
    }
    
private:
    unsigned long get_task_weight(struct task_struct* task) {
        int nice = task_nice(task);
        return prio_to_weight[nice + 20];
    }
    
    bool need_resched(struct task_struct* task) {
        // 타임 슬라이스 소진 여부 확인
        return task->vruntime > get_min_vruntime() + sched_latency();
    }
    
    unsigned long sched_latency() {
        // 스케줄링 지연시간 계산
        return min_granularity * num_active_tasks();
    }
};
```

### 2. 실시간 스케줄링 (Real-time Scheduling)

실시간 시스템에서는 작업의 데드라인을 보장하는 것이 중요합니다.

```mermaid
graph TD
    subgraph "실시간 스케줄링"
        A[EDF] --> D[데드라인 기반]
        B[RMS] --> E[고정 우선순위]
        C[DMS] --> E
        
        D --> F[동적 우선순위]
        E --> G[정적 우선순위]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style G fill:#f9f,stroke:#333,stroke-width:2px
    end
```

EDF(Earliest Deadline First) 스케줄러 구현:
```c
class EDFScheduler {
private:
    struct Task {
        int id;
        chrono::milliseconds period;
        chrono::milliseconds deadline;
        chrono::milliseconds execution_time;
        chrono::steady_clock::time_point next_deadline;
        bool is_periodic;
    };
    
    priority_queue<Task*, vector<Task*>, CompareDeadline> ready_queue;
    vector<Task*> periodic_tasks;
    
public:
    void add_task(Task* task) {
        if (task->is_periodic) {
            task->next_deadline = 
                chrono::steady_clock::now() + task->period;
            periodic_tasks.push_back(task);
        }
        ready_queue.push(task);
    }
    
    void schedule() {
        while (!ready_queue.empty()) {
            auto current_time = chrono::steady_clock::now();
            Task* task = ready_queue.top();
            
            if (task->next_deadline <= current_time) {
                // 데드라인 미스
                handle_deadline_miss(task);
                continue;
            }
            
            // 태스크 실행
            execute_task(task);
            ready_queue.pop();
            
            // 주기적 태스크 재스케줄링
            if (task->is_periodic) {
                task->next_deadline += task->period;
                ready_queue.push(task);
            }
            
            // 새로운 주기적 태스크 확인
            check_periodic_tasks(current_time);
        }
    }
    
private:
    struct CompareDeadline {
        bool operator()(const Task* a, const Task* b) {
            return a->next_deadline > b->next_deadline;
        }
    };
    
    void execute_task(Task* task) {
        // 태스크 실행 시뮬레이션
        this_thread::sleep_for(task->execution_time);
    }
    
    void handle_deadline_miss(Task* task) {
        ready_queue.pop();
        // 데드라인 미스 처리 로직
        cout << "Deadline miss for task " << task->id << endl;
    }
    
    void check_periodic_tasks(
        chrono::steady_clock::time_point current_time) {
        for (auto task : periodic_tasks) {
            if (task->next_deadline <= current_time) {
                task->next_deadline += task->period;
                ready_queue.push(task);
            }
        }
    }
};
```

### 3. 멀티코어 스케줄링

현대의 멀티코어 시스템에서는 코어 간의 부하 분산과 캐시 친화성을 고려한 스케줄링이 필요합니다.

```mermaid
graph TD
    subgraph "멀티코어 스케줄링"
        A[로드 밸런싱] --> D[코어 할당]
        B[캐시 친화도] --> D
        C[NUMA 인지] --> D
        
        E[코어 간 이주] --> F[성능 최적화]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

멀티코어 스케줄러 구현:
```c
class MultiCoreScheduler {
private:
    struct Core {
        vector<Process*> run_queue;
        int load;
        int cache_domain;
        int numa_node;
    };
    
    vector<Core> cores;
    int load_imbalance_threshold;
    
public:
    MultiCoreScheduler(int num_cores, 
                      int threshold)
        : cores(num_cores),
          load_imbalance_threshold(threshold) {
        // 코어 정보 초기화
        for (int i = 0; i < num_cores; i++) {
            cores[i].load = 0;
            cores[i].cache_domain = i / 4;  // 4코어당 캐시 도메인
            cores[i].numa_node = i / 8;     // 8코어당 NUMA 노드
        }
    }
    
    void schedule_process(Process* process) {
        // 최적의 코어 선택
        int target_core = select_best_core(process);
        
        // 프로세스 할당
        cores[target_core].run_queue.push_back(process);
        cores[target_core].load += process->weight;
        
        // 필요시 로드 밸런싱 수행
        if (check_load_imbalance())
            balance_load();
    }
    
private:
    int select_best_core(Process* process) {
        int best_core = 0;
        int min_load = INT_MAX;
        
        for (int i = 0; i < cores.size(); i++) {
            // 로드, 캐시 친화도, NUMA 거리를 고려한 점수 계산
            int score = calculate_core_score(i, process);
            
            if (score < min_load) {
                min_load = score;
                best_core = i;
            }
        }
        
        return best_core;
    }
    
    int calculate_core_score(int core_id, Process* process) {
        int score = cores[core_id].load;
        
        // 캐시 친화도 고려
        if (process->last_core != -1) {
            int cache_penalty = 
                (cores[core_id].cache_domain != 
                 cores[process->last_core].cache_domain) 
                ? 100 : 0;
            score += cache_penalty;
        }
        
        // NUMA 거리 고려
        if (process->numa_node != -1) {
            int numa_penalty = 
                abs(cores[core_id].numa_node - 
                    process->numa_node) * 200;
            score += numa_penalty;
        }
        
        return score;
    }
    
    bool check_load_imbalance() {
        int max_load = 0;
        int min_load = INT_MAX;
        
        for (const auto& core : cores) {
            max_load = max(max_load, core.load);
            min_load = min(min_load, core.load);
        }
        
        return (max_load - min_load) > load_imbalance_threshold;
    }
    
    void balance_load() {
        // 가장 부하가 높은 코어에서 가장 낮은 코어로
        // 프로세스 이주
        for (int i = 0; i < cores.size(); i++) {
            for (int j = 0; j < cores.size(); j++) {
                if (cores[i].load - cores[j].load > 
                    load_imbalance_threshold) {
                    migrate_process(i, j);
                }
            }
        }
    }
    
    void migrate_process(int from_core, int to_core) {
        // 가장 적합한 프로세스 선택 및 이주
        auto& queue = cores[from_core].run_queue;
        if (queue.empty()) return;
        
        // 이주할 프로세스 선택
        auto it = min_element(queue.begin(), queue.end(),
            [](const Process* a, const Process* b) {
                return a->weight < b->weight;
            });
            
        Process* process = *it;
        queue.erase(it);
        
        // 새로운 코어에 할당
        cores[to_core].run_queue.push_back(process);
        cores[from_core].load -= process->weight;
        cores[to_core].load += process->weight;
        
        process->last_core = to_core;
    }
};
```

This implementation demonstrates key features of modern multicore scheduling:

1. 로드 밸런싱
   - 코어 간 부하 분산
   - 동적 프로세스 이주
   - 임계값 기반 밸런싱 결정

2. 캐시 친화도
   - 캐시 도메인 고려
   - 프로세스의 이전 실행 코어 추적
   - 불필요한 캐시 미스 최소화

3. NUMA 인지
   - NUMA 노드 거리 계산
   - 메모리 접근 지연 최소화
   - 로컬 메모리 접근 선호

4. 확장성
   - 다양한 코어 구성 지원
   - 유연한 정책 설정
   - 성능 모니터링 및 조정

이러한 멀티코어 스케줄링 기법들은 현대 시스템의 성능과 효율성을 크게 향상시킵니다.

## E. 고급 스케줄링 최적화 기법

### 1. 에너지 인지 스케줄링 (Energy-Aware Scheduling)

현대 시스템에서 전력 소비를 고려한 스케줄링이 중요해지고 있습니다.

```mermaid
graph TD
    subgraph "에너지 인지 스케줄링"
        A[전력 모니터링] --> D[스케줄링 결정]
        B[CPU 주파수 조절] --> D
        C[코어 온/오프] --> D
        
        D --> E[전력 소비 최적화]
        E --> F[성능 균형]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

구현 예제:
```c
class EnergyAwareScheduler {
private:
    struct Core {
        bool active;
        int current_freq;
        vector<int> available_freqs;
        float power_consumption;
        vector<Process*> processes;
    };
    
    vector<Core> cores;
    float power_budget;
    float temperature_threshold;
    
public:
    void schedule_task(Process* process) {
        // 최적의 코어와 주파수 선택
        auto [target_core, target_freq] = 
            find_optimal_core_freq(process);
            
        if (target_core >= 0) {
            assign_task(process, target_core, target_freq);
        } else {
            handle_overload_situation(process);
        }
    }
    
private:
    pair<int, int> find_optimal_core_freq(Process* process) {
        int best_core = -1;
        int best_freq = -1;
        float min_energy_cost = INFINITY;
        
        for (int i = 0; i < cores.size(); i++) {
            if (!cores[i].active) continue;
            
            for (int freq : cores[i].available_freqs) {
                float energy_cost = calculate_energy_cost(
                    process, i, freq
                );
                
                if (energy_cost < min_energy_cost &&
                    is_within_power_budget(i, freq)) {
                    min_energy_cost = energy_cost;
                    best_core = i;
                    best_freq = freq;
                }
            }
        }
        
        return {best_core, best_freq};
    }
    
    float calculate_energy_cost(Process* process, 
                              int core_id, 
                              int freq) {
        // 에너지 소비 예측 모델
        float base_power = get_base_power(freq);
        float utilization = calculate_utilization(
            cores[core_id], process
        );
        float temperature_factor = get_temperature_factor(
            core_id
        );
        
        return base_power * utilization * temperature_factor;
    }
    
    void adjust_power_state() {
        // DVFS (Dynamic Voltage and Frequency Scaling)
        for (auto& core : cores) {
            if (core.power_consumption > power_budget) {
                decrease_frequency(core);
            } else if (has_performance_headroom(core)) {
                increase_frequency(core);
            }
            
            // 필요시 코어 끄기/켜기
            if (should_deactivate_core(core)) {
                deactivate_core(core);
            } else if (should_activate_core(core)) {
                activate_core(core);
            }
        }
    }
};
```

### 2. QoS 기반 스케줄링 (Quality of Service Scheduling)

서비스 품질 요구사항을 만족시키기 위한 스케줄링 기법입니다.

```mermaid
graph TD
    subgraph "QoS 스케줄링"
        A[SLA 모니터링] --> D[자원 할당]
        B[우선순위 조정] --> D
        C[자원 예약] --> D
        
        D --> E[QoS 보장]
        E --> F[SLA 준수]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

구현 예제:
```c
class QoSScheduler {
private:
    struct ServiceClass {
        int priority;
        float min_cpu_share;
        int max_latency_ms;
        float guaranteed_bandwidth;
    };
    
    map<string, ServiceClass> service_classes;
    map<Process*, string> process_to_class;
    
public:
    void add_service_class(const string& name, 
                          const ServiceClass& sc) {
        service_classes[name] = sc;
    }
    
    void schedule_task(Process* process) {
        auto service_class = get_service_class(process);
        
        if (is_latency_critical(service_class)) {
            schedule_realtime(process, service_class);
        } else {
            schedule_best_effort(process, service_class);
        }
        
        monitor_qos_metrics(process, service_class);
    }
    
private:
    void schedule_realtime(Process* process,
                          const ServiceClass& sc) {
        // 실시간 스케줄링 정책 적용
        int target_core = find_suitable_core(sc);
        
        if (target_core >= 0) {
            assign_to_core(process, target_core);
            reserve_resources(process, sc);
        } else {
            handle_resource_contention(process, sc);
        }
    }
    
    void monitor_qos_metrics(Process* process,
                           const ServiceClass& sc) {
        // QoS 메트릭 모니터링
        float current_latency = measure_latency(process);
        float current_throughput = measure_throughput(process);
        
        if (current_latency > sc.max_latency_ms) {
            handle_qos_violation(process, "latency");
        }
        
        if (current_throughput < sc.guaranteed_bandwidth) {
            handle_qos_violation(process, "throughput");
        }
    }
    
    void handle_qos_violation(Process* process,
                            const string& metric) {
        // QoS 위반 처리
        auto service_class = get_service_class(process);
        
        // 우선순위 조정
        adjust_priority(process, service_class);
        
        // 자원 재할당
        reallocate_resources(process, service_class);
        
        // 위반 로깅 및 알림
        log_qos_violation(process, metric);
    }
};
```

### 3. AI/ML 워크로드 최적화 스케줄링

AI와 머신러닝 워크로드의 특성을 고려한 특화된 스케줄링입니다.

```mermaid
graph TD
    subgraph "AI/ML 스케줄링"
        A[GPU 활용] --> D[리소스 할당]
        B[메모리 패턴] --> D
        C[배치 크기] --> D
        
        D --> E[학습 최적화]
        E --> F[추론 성능]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

구현 예제:
```c
class MLWorkloadScheduler {
private:
    struct GPUDevice {
        int device_id;
        size_t memory_total;
        size_t memory_used;
        vector<Process*> running_jobs;
        float utilization;
    };
    
    vector<GPUDevice> gpus;
    map<Process*, MLJobMetrics> job_metrics;
    
public:
    void schedule_ml_job(Process* process,
                        const MLJobRequirements& reqs) {
        // GPU 선택 및 할당
        int target_gpu = select_gpu(reqs);
        
        if (target_gpu >= 0) {
            allocate_gpu_resources(process, target_gpu, reqs);
            monitor_job_progress(process);
        } else {
            queue_job_for_later(process, reqs);
        }
    }
    
private:
    int select_gpu(const MLJobRequirements& reqs) {
        int best_gpu = -1;
        float best_score = -1;
        
        for (int i = 0; i < gpus.size(); i++) {
            if (can_accommodate_job(gpus[i], reqs)) {
                float score = calculate_gpu_score(gpus[i], reqs);
                if (score > best_score) {
                    best_score = score;
                    best_gpu = i;
                }
            }
        }
        
        return best_gpu;
    }
    
    void monitor_job_progress(Process* process) {
        // 작업 진행 상황 모니터링
        auto& metrics = job_metrics[process];
        
        // 성능 메트릭 수집
        update_job_metrics(process, metrics);
        
        // 필요시 리소스 조정
        if (needs_resource_adjustment(metrics)) {
            adjust_resources(process, metrics);
        }
        
        // 학습 진행률 체크
        if (is_training_job(process)) {
            check_training_progress(process, metrics);
        }
    }
    
    void adjust_resources(Process* process,
                         const MLJobMetrics& metrics) {
        // 동적 배치 크기 조정
        if (metrics.gpu_memory_pressure > threshold) {
            reduce_batch_size(process);
        }
        
        // 메모리 최적화
        if (metrics.memory_swapping_detected) {
            optimize_memory_usage(process);
        }
        
        // GPU 병렬화 조정
        if (can_benefit_from_more_gpus(metrics)) {
            scale_out_to_more_gpus(process);
        }
    }
};
```

### 4. 컨테이너 오케스트레이션 스케줄링

현대 클라우드 환경에서의 컨테이너 스케줄링 기법입니다.

```mermaid
graph TD
    subgraph "컨테이너 스케줄링"
        A[리소스 요구사항] --> D[노드 선택]
        B[어피니티 규칙] --> D
        C[제약 조건] --> D
        
        D --> E[배치 결정]
        E --> F[스케일링]
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

구현 예제:
```c
class ContainerScheduler {
private:
    struct Node {
        string id;
        ResourceCapacity capacity;
        ResourceUsage current_usage;
        vector<Container*> containers;
        map<string, string> labels;
    };
    
    vector<Node> nodes;
    map<string, Affinity> affinities;
    
public:
    void schedule_container(Container* container,
                          const ContainerSpec& spec) {
        // 노드 선택
        auto suitable_nodes = filter_nodes(spec);
        auto ranked_nodes = rank_nodes(suitable_nodes, spec);
        
        if (!ranked_nodes.empty()) {
            Node* target_node = ranked_nodes[0];
            deploy_container(container, target_node, spec);
        } else {
            handle_scheduling_failure(container, spec);
        }
    }
    
private:
    vector<Node*> filter_nodes(const ContainerSpec& spec) {
        vector<Node*> candidates;
        
        for (auto& node : nodes) {
            if (meets_resource_requirements(node, spec) &&
                satisfies_constraints(node, spec) &&
                matches_affinity_rules(node, spec)) {
                candidates.push_back(&node);
            }
        }
        
        return candidates;
    }
    
    vector<Node*> rank_nodes(const vector<Node*>& candidates,
                           const ContainerSpec& spec) {
        // 노드 순위 계산
        vector<pair<Node*, float>> scores;
        
        for (auto node : candidates) {
            float score = calculate_node_score(node, spec);
            scores.push_back({node, score});
        }
        
        // 점수 기준 정렬
        sort(scores.begin(), scores.end(),
             [](const auto& a, const auto& b) {
                 return a.second > b.second;
             });
             
        vector<Node*> ranked_nodes;
        transform(scores.begin(), scores.end(),
                 back_inserter(ranked_nodes),
                 [](const auto& pair) { return pair.first; });
                 
        return ranked_nodes;
    }
    
    float calculate_node_score(Node* node,
                             const ContainerSpec& spec) {
        float resource_score = calculate_resource_score(node, spec);
        float spread_score = calculate_spread_score(node, spec);
        float locality_score = calculate_locality_score(node, spec);
        
        return resource_score * 0.5 +
               spread_score * 0.3 +
               locality_score * 0.2;
    }
    
    void deploy_container(Container* container,
                         Node* node,
                         const ContainerSpec& spec) {
        // 컨테이너 배포
        reserve_resources(node, spec);
        create_container(node, container, spec);
        update_node_state(node);
        
        // 모니터링 설정
        setup_monitoring(container, node);
        
        // 네트워킹 설정
        configure_networking(container, node);
    }
};
```

### 5. 미래 트렌드와 과제

현대 스케줄링 시스템이 직면한 주요 과제와 향후 발전 방향입니다:

```mermaid
graph TD
    subgraph "미래 스케줄링 과제"
        A[하이브리드 워크로드] --> D[최적화 목표]
        B[자원 효율성] --> D
        C[확장성] --> D
        
        E[새로운 아키텍처] --> F[미래 시스템]
        D --> F
        
        style A fill:#f96,stroke:#333,stroke-width:2px
        style D fill:#9cf,stroke:#333,stroke-width:2px
        style F fill:#f9f,stroke:#333,stroke-width:2px
    end
```

1. 하이브리드 워크로드 최적화
   * 다양한 워크로드 특성 고려
   * 자원 효율성과 성능 균형
   * 동적 부하 적응

2. 이종 컴퓨팅 환경 지원
   * CPU/GPU/TPU/FPGA 통합 관리
   * 하드웨어 가속기 최적 활용
   * 이기종 프로세서 간 작업 분배

3. 자율 스케줄링
   * AI 기반 의사결정
   * 자가 적응형 시스템
   * 예측적 자원 할당

4. 확장성과 신뢰성
   * 대규모 분산 시스템 지원
   * 장애 복구 메커니즘
   * 일관성 보장

5. 새로운 컴퓨팅 패러다임 대응
   * 양자 컴퓨팅 통합
   * 엣지 컴퓨팅 최적화
   * 서버리스 아키텍처

구현 예제:
```c
class NextGenScheduler {
private:
    struct ResourcePool {
        vector<CPU*> cpus;
        vector<GPU*> gpus;
        vector<TPU*> tpus;
        vector<FPGA*> fpgas;
        vector<QuantumProcessor*> quantum_processors;
    };
    
    struct WorkloadPredictor {
        MLModel resource_usage_model;
        MLModel performance_model;
        MLModel failure_predictor;
    };
    
    ResourcePool resources;
    WorkloadPredictor predictor;
    AIDecisionMaker decision_maker;
    
public:
    void schedule_workload(Workload* workload) {
        // 워크로드 분석
        auto characteristics = analyze_workload(workload);
        
        // 미래 자원 요구사항 예측
        auto future_demands = 
            predictor.predict_resource_demands(workload);
        
        // 최적 실행 계획 수립
        auto execution_plan = 
            decision_maker.create_optimal_plan(
                characteristics,
                future_demands,
                resources
            );
        
        // 실행 계획 적용
        execute_plan(workload, execution_plan);
        
        // 성능 모니터링 및 피드백
        monitor_and_adjust(workload, execution_plan);
    }
    
private:
    WorkloadCharacteristics analyze_workload(
        Workload* workload) {
        return {
            .compute_intensity = 
                measure_compute_intensity(workload),
            .memory_pattern = 
                analyze_memory_access_pattern(workload),
            .data_locality = 
                evaluate_data_locality(workload),
            .parallelism = 
                estimate_parallelism_degree(workload)
        };
    }
    
    void execute_plan(Workload* workload,
                     const ExecutionPlan& plan) {
        // 자원 할당
        allocate_resources(workload, plan);
        
        // 워크로드 배포
        deploy_workload(workload, plan);
        
        // 실행 환경 최적화
        optimize_runtime_environment(workload, plan);
        
        // 모니터링 설정
        setup_advanced_monitoring(workload);
    }
    
    void monitor_and_adjust(Workload* workload,
                          const ExecutionPlan& plan) {
        while (workload->is_running()) {
            // 성능 메트릭 수집
            auto metrics = collect_performance_metrics(workload);
            
            // 이상 징후 감지
            if (detect_anomalies(metrics)) {
                handle_anomalies(workload, metrics);
            }
            
            // 자원 사용 최적화
            if (need_optimization(metrics)) {
                optimize_resource_usage(workload, metrics);
            }
            
            // 실행 계획 갱신
            update_execution_plan(workload, plan, metrics);
        }
    }
    
    void handle_anomalies(Workload* workload,
                         const PerformanceMetrics& metrics) {
        // 장애 예측
        if (predictor.failure_predictor.predict_failure(metrics)) {
            initiate_preventive_actions(workload);
        }
        
        // 성능 저하 대응
        if (metrics.performance_degradation_detected) {
            mitigate_performance_issues(workload);
        }
        
        // 자원 경합 해결
        if (metrics.resource_contention_detected) {
            resolve_resource_contention(workload);
        }
    }
};
```

이러한 미래 지향적 스케줄러는 다음과 같은 특징을 가집니다:

1. 적응형 의사결정
   * AI/ML 기반 예측
   * 실시간 성능 최적화
   * 동적 자원 재할당

2. 복합 워크로드 처리
   * 다중 프로세서 아키텍처 지원
   * 워크로드 특성 기반 최적화
   * 자원 사용 효율성 극대화

3. 자가 관리
   * 자동 장애 감지 및 복구
   * 성능 자동 튜닝
   * 예방적 유지보수

4. 확장 가능한 아키텍처
   * 새로운 컴퓨팅 리소스 통합
   * 유연한 정책 적용
   * 플러그인 기반 확장성

이러한 발전은 더욱 복잡해지는 컴퓨팅 환경에서 효율적인 자원 관리를 가능하게 할 것입니다.