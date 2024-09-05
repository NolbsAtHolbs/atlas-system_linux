#include "multithreading.h"

/**
 * create_task - Creates a new task with a specified entry function and param
 * @entry: Pointer to the function that serves as the task entry point.
 * @param: Pointer to the parameter to be passed to the task entry function.
 *
 * Return: Pointer to the newly created task structure, or NULL if memaloc fail
 */
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task = malloc(sizeof(task_t));
	static int next_task_id;

	if (!task)
		return (NULL);

	task->entry = entry;
	task->param = param;
	task->status = PENDING;
	task->result = NULL;
	pthread_mutex_init(&task->lock, NULL);
	task->id = next_task_id++;  /* Assign a unique task ID */

	return (task);
}

/**
 * destroy_task - Frees resources associated with a task.
 * @task: Pointer to the task to destroy.
 *
 * This function deallocates the memory of the specified task, including result
 * and mutex, if necessary.
 */
void destroy_task(task_t *task)
{
	if (task)
	{
		list_destroy(task->result, free);
		free(task->result);
		free(task);
	}
}

/**
 * exec_tasks - Executes a list of tasks in a thread-safe manner.
 * @tasks: Pointer to the list of tasks to execute.
 *
 * function ensures that each task is processed by multiple threads in thrdsafe
 * manner. Tasks are executed only once, and their status updated accordingly
 * Uses a mutex to print the status of each task without race conditions.
 *
 * Return: Always returns NULL.
 */
void *exec_tasks(const list_t *tasks)
{
	node_t *current_node;
	task_t *task;
	pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

	/* Start from the head of the list */
	current_node = tasks->head;

	while (current_node)
	{
		pthread_mutex_lock(&print_mutex);

		task = (task_t *)current_node->content;

		if (task->status == PENDING)
		{
			task->status = STARTED;
			tprintf("[%02d] Started\n", task->id);
			pthread_mutex_unlock(&print_mutex);

			task->result = task->entry(task->param);

			pthread_mutex_lock(&print_mutex);
			task->status = SUCCESS;
			tprintf("[%02d] Success\n", task->id);
		}
		else
		{
			pthread_mutex_unlock(&print_mutex);
		}

		pthread_mutex_unlock(&print_mutex);

		current_node = current_node->next;
	}

	return (NULL);
}
