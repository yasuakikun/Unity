using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HPBarCtl: MonoBehaviour {
    private PlayerHP playerhp;
    private Slider slider;

    public Transform bartransform;
    public Transform activetransform;

    private float nowRate;

    private Coroutine barCoroutine;

    void Bar()
    {
        bartransform.localScale = new Vector3(1, 1, 1);
        activetransform.localScale = new Vector3(1, 1, 1);
    }

    // Use this for initialization
    void Start ()
    {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void SetBar(int now, int max)
    {
        nowRate = (float)now / max;
        bartransform.localScale = new Vector3(nowRate, 1, 1);
        if (barCoroutine != null)
        {
            StopCoroutine(barCoroutine);
        }
        barCoroutine = StartCoroutine("ChangeActiveBar");
    }

    IEnumerator ChangeActiveBar()
    {
        yield return new WaitForSeconds(0.6f);
        float beforeRate = activetransform.localScale.x;
        if (nowRate > beforeRate)
        {
            beforeRate = nowRate;
            activetransform.localScale = new Vector3(nowRate, 1, 1);
        }
        Vector3 vec = activetransform.localScale;
        float sa = (beforeRate - nowRate) / 10;

        while (beforeRate > nowRate)
        {
            beforeRate = UnityEngine.Mathf.Max(beforeRate - sa, 0);
            activetransform.localScale = new Vector3(beforeRate, vec.y, vec.z);
            yield return null;
        }
    }
}
