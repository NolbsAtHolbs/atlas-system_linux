#include "multithreading.h"

/**
 * create_task - Creates a new task
 * @entry: Pointer to the task entry function
 * @param: Parameter to pass to the entry function
 * Return: A pointer to the created task
 */
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task = malloc(sizeof(task_t));

	if (!task)
		return (NULL);

	task->entry = entry;
	task->param = param;
	task->status = PENDING;
	task->result = NULL;
	pthread_mutex_init(&task->lock, NULL);
	return (task);
}

/**
 * destroy_task - Destroys a task
 * @task: Pointer to the task to destroy
 */
void destroy_task(task_t *task)
{
	pthread_mutex_destroy(&task->lock);
	free(task);
}

/**
 * exec_tasks - Executes tasks from the list
 * @tasks: Pointer to the list of tasks
 * Return: NULL
 */
void *exec_tasks(list_t const *tasks)
{
	node_t *node;

	for (node = tasks->head; node; node = node->next)
	{
		task_t *task = (task_t *)node->content;

		pthread_mutex_lock(&task->lock);
		if (task->status == PENDING)
		{
			tprintf("[STARTED] Task: %s\n", (char *)task->param);
			task->status = STARTED;
			task->result = task->entry(task->param); /* Execute the task */
			task->status = SUCCESS;
			tprintf("[SUCCESS] Task: %s\n", (char *)task->param);
		}
		pthread_mutex_unlock(&task->lock);
	}
	return (NULL);
}
