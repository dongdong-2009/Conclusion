using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using NLog;

namespace ClockTick
{
    public enum eTimingPattern
    {
        SleepSec,
        MultiThreadTimer
    }

    public class ClockTickClass:IDisposable
    {
        private Logger m_Logger;

        /// <summary>
        /// 秒级别时间的计时线程
        /// </summary>
        private CyclicRunThreadClass m_TickSecondThread;
        /// <summary>
        /// 分钟级别时间的计时线程
        /// </summary>
        private CyclicRunThreadClass m_TickMinuteThread;


        private int m_LastMinute;
        public delegate void CyclicRunHandler();

        /// <summary>
        /// 每隔X秒响应函数
        /// </summary>
        public event CyclicRunHandler OnXSecond;
        /// <summary>
        /// 每隔一分钟响应函数
        /// </summary>
        public event CyclicRunHandler OnOneMinute;
        /// <summary>
        /// 每隔半小时响应函数
        /// </summary>
        public event CyclicRunHandler OnHalfAnHour;
        /// <summary>
        /// 每隔一小时响应函数
        /// </summary>
        public event CyclicRunHandler OnOneHour;
        /// <summary>
        /// 每隔一天响应函数
        /// </summary>
        public event CyclicRunHandler OnOneDay;

        public eTimingPattern ClockType = eTimingPattern.SleepSec;

        /// <summary>
        /// 间隔时间X秒，默认为1
        /// </summary>
        public int XSecond
        {
            set
            {
                m_XSecond = value;
            }
            get
            {
                return m_XSecond;
            }
        }
        private int m_XSecond;
        private long m_LastTimeStamp;


        public ClockTickClass(int PollSecond = 1)
        {
            m_TickSecondThread = new CyclicRunThreadClass();
            m_TickSecondThread.Interval = 200;
            m_TickSecondThread.TimingPattern = ClockType;
            m_TickSecondThread.CyclicRun += TickClockSecond;

            m_TickMinuteThread = new CyclicRunThreadClass();
            m_TickMinuteThread.Interval = 200;
            m_TickMinuteThread.TimingPattern = ClockType;
            m_TickMinuteThread.CyclicRun += TickClockMinute;


            DateTime CurrentTime = System.DateTime.Now;
            m_LastMinute = CurrentTime.Minute;
            m_LastTimeStamp = ConvertTimeToUnix(System.DateTime.Now);
            if (PollSecond>=1 && PollSecond<=60)
            {
                m_XSecond = PollSecond;
            }
            else
            {
                m_XSecond = 1;
            }
            m_Logger = LogManager.GetCurrentClassLogger();
        }

        public void Start()
        {
            m_TickSecondThread.StartThead();
            m_TickMinuteThread.StartThead();
        }
        public void Stop()
        {
            if (m_TickSecondThread != null)
            {
                m_TickSecondThread.StopThead();
            }
            if (m_TickMinuteThread != null)
            {
                m_TickMinuteThread.StopThead();
            }
        }
        public void Dispose()
        {
            if (m_TickSecondThread != null)
            {
                m_TickSecondThread.StopThead();
            }
            if (m_TickMinuteThread != null)
            {
                m_TickMinuteThread.StopThead();
            }
        }
        private void TickClockSecond()
        {
            try
            {
                DateTime CurrentTime = System.DateTime.Now;
                long CurrentTimeStamp = ConvertTimeToUnix(CurrentTime);
                int Sec = CurrentTime.Second;
                int Min = CurrentTime.Minute;
                int Hour = CurrentTime.Hour; //返回结果:小时组成部分，表示为 0 和 23 之间的一个值。
                if (CurrentTimeStamp - m_LastTimeStamp >= m_XSecond)
                {
                    m_LastTimeStamp = CurrentTimeStamp;
                    OnXSecond();
                }
            }
            catch (Exception ex)
            {
                m_Logger.Error(ex);
            }
            
        }

        private void TickClockMinute()
        {
            try
            {
                DateTime CurrentTime = System.DateTime.Now;
                long CurrentTimeStamp = ConvertTimeToUnix(CurrentTime);
                int Sec = CurrentTime.Second;
                int Min = CurrentTime.Minute;
                int Hour = CurrentTime.Hour; //返回结果:小时组成部分，表示为 0 和 23 之间的一个值。

                //m_Log.Logger.Info(string.Format("ClockTickClass.TickClockMinute: m_LastMinute={0}, Min={1}, Sec={2};", m_LastMinute, Min, Sec));
                if (Sec.Equals(0) && m_LastMinute != Min) //整分
                {
                    m_LastMinute = Min;
                    // m_Log.Logger.Info(string.Format("ClockTickClass.TickClockMinute: m_LastMinute={0}, Min={1}, Sec={2};", m_LastMinute, Min, Sec));
                    OnOneMinute();
                  //  m_Log.Logger.Info(string.Format("ClockTickClass.TickClockMinute: OnOneMinute() return."));
                    //累积计时方式
                    //CounterMin_30++;
                    //if (CounterMin_30 >= 30)
                    //{
                    //    CounterMin_30 = 0;
                    //    OnHalfAnHour();
                    //}
                    if (Min.Equals(30))//半小时
                    {
                        OnHalfAnHour();
                    }
                    if (Min.Equals(0))//整时
                    {
                        OnHalfAnHour();
                        OnOneHour();
                        if (Hour.Equals(0)) //整天
                        {
                            OnOneDay();
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                m_Logger.Error(ex);
            }

        }

        #region [ConvertTimeToUnix] DateTime时间格式转换为Unix时间戳格式
        /// <summary>
        /// 将c# DateTime时间格式转换为Unix时间戳格式
        /// </summary>
        /// <param name="time">时间</param>
        /// <returns>long</returns>
        public static long ConvertTimeToUnix(System.DateTime time)
        {
            System.DateTime startTime = TimeZone.CurrentTimeZone.ToLocalTime(new System.DateTime(1970, 1, 1, 0, 0, 0, 0));
            long t = Convert.ToInt64((time - startTime).TotalSeconds);
            return t;
        }
        #endregion
    }

    public class CyclicRunThreadClass
    {
        #region [Interval] 运行时间间隔
        private int m_Interval = 1;
        /// <summary>
        /// 定时间隔,毫秒
        /// </summary>
        public int Interval
        {
            get { return m_Interval; }
            set { m_Interval = value; }
        }
        #endregion

        #region [TimingPattern] 运行计时方式
        public eTimingPattern TimingPattern = eTimingPattern.SleepSec;

        #endregion

        #region [IsRunOnce] 是否是循环运行，false:只运行一次
        private bool m_IsCyclicRun = true;
        /// <summary>
        /// 是否是循环运行，默认为true，false:只运行一次
        /// </summary>
        public bool IsCyclicRun
        {
            get { return m_IsCyclicRun; }
            set { m_IsCyclicRun = value; }
        }
        #endregion

        #region [SleepMSec] 运行间隔之外的等待时间
        private int m_SleepMSec = 0;
        public int SleepMSec
        {
            get { return m_SleepMSec; }
            set { m_SleepMSec = value; }
        }
        #endregion

        public delegate void CyclicRunHandler();
        public event CyclicRunHandler CyclicRun;
        public System.Timers.Timer m_MultiThreadTimer;
        private Thread m_Thread;
        private bool m_IsExit = false;

        public void StartThead()
        {
            if (m_Thread == null || !m_Thread.IsAlive)
            {
                this.m_Thread = new Thread(new ThreadStart(RunThead));
                this.m_Thread.IsBackground = true; //该线程为后台线程
                this.m_Thread.Name = Guid.NewGuid().ToString();
                this.m_Thread.Start();
            }
        }

        private void RunThead()
        {
            if (m_Interval == 1)
            {
                m_IsCyclicRun = false;
            }
            switch (TimingPattern)
            {
                case eTimingPattern.MultiThreadTimer:
                    {

                        m_MultiThreadTimer = new System.Timers.Timer();
                        m_MultiThreadTimer.Interval = m_Interval;
                        //设置是执行一次（false）还是一直执行(true)；
                        m_MultiThreadTimer.AutoReset = m_IsCyclicRun;
                        m_MultiThreadTimer.Elapsed += OnMultiThreadTimerElapsed;
                        m_MultiThreadTimer.Start();
                        break;
                    }
                case eTimingPattern.SleepSec:
                    {
                        while (!m_IsExit)
                        {
                            if (m_IsExit) //如果标识为 true，则退出循环，退出线程
                            {
                                break;
                            }
                            //处理事务
                            CyclicRun();
                            Thread.Sleep(m_Interval);
                            if (!m_IsCyclicRun)
                            {
                                return;
                            }
                        }
                        break;
                    }
                default:
                    {
                        break;
                    }
            }

        }

        private void OnMultiThreadTimerElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            CyclicRun();
        }

        public void StopThead()
        {
            if (this.m_Thread != null)
            {
                if (m_MultiThreadTimer != null)
                {
                    m_MultiThreadTimer.Stop();
                }
                this.m_IsExit = true; //标识当前线程为可退出线程。
                this.m_Thread.Join(1000);//阻塞调用线程，直到某个线程终止或经过了指定时间为止
                try
                {
                    m_Thread.Abort(); //为了防止线程没有退出，进行强行终止，有可能造成文件损坏
                }
                catch (Exception)
                {
                    //m_Logger.Error(ex);
                }
            }
        }

    }
}
