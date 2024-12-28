import (
	"fmt"
	"go.uber.org/zap"
	"go.uber.org/zap/zapcore"
	"os"
	"path/filepath"
	"time"
)

// InitLogger 初始化 zap 日志
func InitLogger() *zap.Logger {
	// 获取当前日期
	currentDate := time.Now().Format("2006-01-02")
	// 日志目录：log/日期/
	logDir := filepath.Join("log", currentDate)

	// 创建日志目录
	if err := os.MkdirAll(logDir, 0755); err != nil {
		panic(fmt.Sprintf("failed to create log directory: %v", err))
	}

	// 创建日志文件路径
	infoLogFile := filepath.Join(logDir, "info.log")
	errorLogFile := filepath.Join(logDir, "error.log")
	debugLogFile := filepath.Join(logDir, "debug.log")
	warningLogFile := filepath.Join(logDir, "warning.log")

	// 创建日志文件的 WriteSyncer
	infoLogWriter := getLogWriter(infoLogFile)
	errorLogWriter := getLogWriter(errorLogFile)
	debugLogWriter := getLogWriter(debugLogFile)
	warningLogWriter := getLogWriter(warningLogFile)

	// 配置带颜色的编码器
	coloredEncoder := zapcore.NewConsoleEncoder(zapcore.EncoderConfig{
		TimeKey:      "time",
		LevelKey:     "level",
		MessageKey:   "msg",
		EncodeLevel:  zapcore.CapitalColorLevelEncoder, // 带颜色的日志级别
		EncodeTime:   zapcore.ISO8601TimeEncoder,       // 时间格式
		EncodeCaller: zapcore.ShortCallerEncoder,       // 输出调用者
		LineEnding:   zapcore.DefaultLineEnding,
	})

	// 创建不同级别的 core
	infoCore := zapcore.NewCore(coloredEncoder, infoLogWriter, zap.LevelEnablerFunc(func(lvl zapcore.Level) bool {
		return lvl == zapcore.InfoLevel // 只记录 INFO 日志
	}))
	errorCore := zapcore.NewCore(coloredEncoder, errorLogWriter, zap.LevelEnablerFunc(func(lvl zapcore.Level) bool {
		return lvl == zapcore.ErrorLevel // 只记录 ERROR 日志
	}))
	warningCore := zapcore.NewCore(coloredEncoder, warningLogWriter, zap.LevelEnablerFunc(func(lvl zapcore.Level) bool {
		return lvl == zapcore.WarnLevel // 只记录 WARN 日志
	}))
	debugCore := zapcore.NewCore(coloredEncoder, debugLogWriter, zap.LevelEnablerFunc(func(lvl zapcore.Level) bool {
		return lvl >= zapcore.DebugLevel // 记录所有日志类型
	}))
	consoleCore := zapcore.NewCore(coloredEncoder, zapcore.AddSync(os.Stdout), zapcore.DebugLevel)

	// 合并所有 core
	core := zapcore.NewTee(infoCore, errorCore, warningCore, debugCore, consoleCore)

	// 返回 logger
	return zap.New(core, zap.AddCaller(), zap.AddStacktrace(zapcore.ErrorLevel))
}

// getLogWriter 创建日志写入器
func getLogWriter(filename string) zapcore.WriteSyncer {
	file, err := os.OpenFile(filename, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		panic(fmt.Sprintf("failed to open log file: %v", err))
	}
	return zapcore.AddSync(file)
}

// func main() {
// 	// 初始化日志
// 	logger := ZapLog.InitLogger()
// 	defer logger.Sync() // 确保日志缓冲区写入

// 	// 示例日志输出
// 	logger.Debug("This is a debug message")
// 	logger.Info("This is an info message")
// 	logger.Warn("This is a warning message")
// 	logger.Error("This is an error message")
// }
