
# ---
# movie
FINALIZE_FRAME_RATE = 29.98
FINALIZE_WIDTH = 640
FINALIZE_HEIGHT = 360


# ---
# base path
PATH_BASE_ASSETS = "../../Assets/"
PATH_BASE_DOWNLOADS = "../../Downloads/"
PATH_BASE_MOVIES = "../../Movies/"


# ----
# source
PATH_SRC_FRAMES_DIR = PATH_BASE_ASSETS + "frames_original/"
PATH_SRC_RESIZE_DIR = PATH_BASE_ASSETS + "frames_resized/"
PATH_SRC_THUMBS_DIR = PATH_BASE_ASSETS + "thumbnails/"
PATH_SRC_NOTFOUND_IMG = PATH_BASE_ASSETS + "notfound.jpg"


# ---
# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
TODAY = Time.now.year.to_s + "-" + Time.now.month.to_s + "-" + Time.now.day.to_s # yyyy-mm-dd
SRC_FRAME_EXTENTION = 'png'
SRC_MOVIE_FILE = PATH_BASE_ASSETS + "sfpc-20131018.MOV"


# ---
# download results
#   [yyyy-mm-dd]
#   - [raw]
#   - [framed]
#   - [thumbs]
PATH_DL_RAWFILES_DIR = PATH_BASE_DOWNLOADS + TODAY + "/raw/"
PATH_DL_FRAMED_DIR = PATH_BASE_DOWNLOADS + TODAY + "/framed/"
PATH_DL_THUMBS_DIR = PATH_BASE_DOWNLOADS + TODAY + "/thumbs/"



# ---
# new movies
# [yyyy-mm-dd]
#   - synth.mov
#   - [frames]
PATH_MOVIE_TODAY_DIR = PATH_BASE_MOVIES + TODAY + "/"
PATH_MOVIE_NEW = PATH_MOVIE_TODAY_DIR + "synth.mov"
PATH_MOVIE_FRAMES_DIR = PATH_MOVIE_TODAY_DIR + "frames/"
