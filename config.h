/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 12;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=16" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#D8DEE9";
static const char col_gray2[]       = "#D8DEE9";
static const char col_gray3[]       = "#434C5E";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#6790EB";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
  [SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };/* "6", "7", "8", "9" };*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
  { "QQ",       NULL,       NULL,       0,            1,           -1 },
  { "steam",    NULL,       NULL,       0,            1,           -1 },
  { "yesplaymusic",         NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

/* Custom Commands*/
static const char *filecmd[]  = { "nautilus", NULL };
static const char *music[] = { "/opt/YesPlayMusic/yesplaymusic", NULL };
static const char *rofi[] = { "rofi", "-show", "drun", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *change_video_wallpaper[] = { "/home/luoyu/壁纸/launch_video_wallpaper.sh", NULL };
static const char *change_to_feh[] = { "/home/luoyu/壁纸/change_to_feh.sh", NULL };
static const char *lock_screen[] = { "i3lockblur", NULL };
static const char *screenshot[] = { "flameshot", "gui", NULL };
static const char *chromium[] = {"chromium", NULL };

/* MultiMedia Control */
static const char *play_pause[] = { "playerctl", "play-pause", NULL };
static const char *stop[] = { "playerctl", "stop", NULL };
static const char *previous[] = { "playerctl", "previous", NULL };
static const char *next[] = { "playerctl", "next", NULL };

/* Brightness Control */
static const char *lightup[] = { "light", "-A", "10", NULL };
static const char *lightdown[] = { "light", "-U", "5", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
  // Addition
  /*
   * { MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
   * { MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
  */

  // Custom Keys
  { MODKEY,                       XK_r,      spawn,	   {.v = rofi } },
	{ MODKEY,                       XK_m,      spawn,	   {.v = music } },
	{ MODKEY,                       XK_F1,     spawn,	   {.v = browser } },
  { MODKEY,                       XK_F2,     spawn,    {.v = chromium } },
	{ MODKEY,                       XK_Return, spawn, 	 {.v = termcmd } },
  { ALTKEY,                       XK_l,      spawn,    {.v = lock_screen } },
 	{ ALTKEY,                       XK_c,      spawn,    {.v = change_video_wallpaper } },
  { ALTKEY,                       XK_x,      spawn,    {.v = change_to_feh } },
  { 0,                            XK_Print,  spawn,    {.v = screenshot } },
  { MODKEY|ShiftMask,             XK_Return, spawn,    {.v = filecmd } },

  // Fullscreen
  { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },

  // MultiMedia Control
  { 0,                            XF86XK_AudioPlay, spawn,    {.v = play_pause } },
  { 0,                            XF86XK_AudioStop, spawn,    {.v = stop } },
  { 0,                            XF86XK_AudioPrev, spawn,    {.v = previous } },
  { 0,                            XF86XK_AudioNext, spawn,    {.v = next } },

  //Brightness Control
  { 0,                            XF86XK_MonBrightnessUp,   spawn,  {.v = lightup } },
  { 0,                            XF86XK_MonBrightnessDown, spawn,  {.v = lightdown } },

  // Awesome Bar
	{ MODKEY|ShiftMask,             XK_s,      showall,        {0} },
	{ MODKEY,                       XK_h,      hide,           {0} },
  { MODKEY,                       XK_s,      show,           {0} }, 
  { MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
  { MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
  { MODKEY,                       XK_Right,  focusstackvis,  {.i = +1 } },
  { MODKEY,                       XK_Left,   focusstackvis,  {.i = -1 } },


  /* 
   * { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
   * { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_c,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY,                       XK_bracketleft,       setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_bracketright,      setmfact,       {.f = +0.05} },
  // Useless For Me
  /*
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  */
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

