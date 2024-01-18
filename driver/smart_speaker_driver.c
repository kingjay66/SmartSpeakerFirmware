#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/init.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Herman Berdnikov");
MODULE_DESCRIPTION("Smart Speaker Firmware Kernel Module");
MODULE_VERSION("0.1-pre-alpha");

#define LOG_INFO(MSG)      printk(KERN_INFO "SSF: " MSG "\n")

#define ERR_CHECK(ERR)     if (ERR != 0) return ERR

static int spi_disp_init(void);

static int __init ssf_start(void) {
  int err;

  LOG_INFO("Loading Smart Speaker Kernel module...");

  err = spi_disp_init();
  ERR_CHECK(err);

  LOG_INFO("Smart Speaker Kernel module initialized successfully");
  return 0;
}

static void __exit ssf_end(void) {
  LOG_INFO("Unloading Smart Speaker Kernel module...");

  LOG_INFO("Smart Speaker Kernel module unloaded successfully.");
}

static int spi_disp_init(void) {
  return 0;
}

module_init(ssf_start);
module_exit(ssf_end);

